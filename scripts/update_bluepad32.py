import requests
import os
import json
import shutil
import zipfile
import update_environments
import rich
import rich.progress
import pathlib

cons = rich.console.Console()

framework_name = "framework-arduinoespressif32"
package_index_url = "https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json"
dirname = os.path.dirname(os.path.abspath(__file__))
platformio_ini_path = os.path.join(dirname, "..", "platformio.ini")

def zip_dir(folder_path: str, output_zip: str) -> None:
    """
    Zips all contents of a folder, including hidden files and subdirectories.

    Parameters:
    - folder_path: str → Path to the folder to zip
    - output_zip: str → Path of the output ZIP file
    """
    with zipfile.ZipFile(output_zip, "w", zipfile.ZIP_DEFLATED) as zipf:
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                file_path = os.path.join(root, file)
                arcname = os.path.relpath(file_path, folder_path)
                zipf.write(file_path, arcname)

def main():
    package_index = requests.get(package_index_url).json()["packages"][0]
    latest_platform = package_index["platforms"][0]
    
    cons.print(f"Found latest package with version v{latest_platform['version']}")
    
    platform_zip_url: str = latest_platform["url"]
    platform_zip_name = platform_zip_url.removesuffix("/").split("/")[-1]

    zip_filename = os.path.join(dirname, platform_zip_name)
    if os.path.exists(zip_filename):
        cons.print("Using cached zip file")
    else:
        cons.print(f"Downloading {platform_zip_name}...")
        with requests.get(platform_zip_url, stream=True) as r:
            r.raise_for_status()
            total_size = int(r.headers.get('content-length', 0))
            block_size = 1024
            with open(zip_filename, 'wb') as f, rich.progress.Progress(
                "[progress.description]{task.description}",
                rich.progress.BarColumn(),
                rich.progress.DownloadColumn(),
                rich.progress.TransferSpeedColumn(),
                rich.progress.TimeRemainingColumn(),
            ) as progress:
                task = progress.add_task("Downloading...", total=total_size)
                for data in r.iter_content(block_size):
                    f.write(data)
                    progress.update(task, advance=len(data))
        cons.print("Download complete.")

    cons.print("Writing package data to zip file...")
    temp_extract_dir = os.path.join(dirname, "temp_bluepad32")
    if os.path.exists(temp_extract_dir):
        shutil.rmtree(temp_extract_dir)

    with zipfile.ZipFile(zip_filename, 'r') as zip:
        zip.extractall(temp_extract_dir)
    cons.print("Extraction complete.")

    cons.print("Updating platform data...")
    framework_dir = os.path.join(temp_extract_dir, pathlib.Path(zip_filename).stem)
    if not os.path.exists(framework_dir):
        cons.print(f"[red]Error: Extracted framework directory {framework_dir} does not exist.")
        return
    package_file = os.path.join(framework_dir, "package.json")
    if not os.path.exists(package_file):
        cons.print(f"[red]Error: package.json not found in {framework_dir}.")
        return
    with open(package_file, 'r+') as f:
        package_config = json.load(f)
        package_config["name"] = framework_name

        f.seek(0)
        f.truncate(0)
        json.dump(package_config, f, indent=4)
        f.truncate()
    cons.print("Platform data updated.")

    cons.print("Repackaging framework...")

    new_zip_filename = os.path.join(dirname, f"{framework_name}-bluepad32-{latest_platform['version']}.zip")

    zip_dir(framework_dir, new_zip_filename)
    cons.print(f"Repackaging complete: {new_zip_filename}")

    cons.print("Cleaning up temporary files...")
    shutil.rmtree(temp_extract_dir)
    # os.remove(zip_filename)
    cons.print("Cleanup complete.")

    cons.print("Moving new package to the frameworks directory...")
    frameworks_dir = os.path.join(dirname, "..", "src", "frameworks")
    new_zip_latest_filename = os.path.join(dirname, f"{framework_name}-bluepad32-latest.zip")
    if not os.path.exists(frameworks_dir):
        os.makedirs(frameworks_dir)
    dest = os.path.join(frameworks_dir, os.path.basename(new_zip_filename))
    if os.path.exists(dest):
        os.remove(dest)
    shutil.move(new_zip_filename, dest)

    cons.print("Updating \"latest\" package...")
    if os.path.exists(new_zip_latest_filename):
        os.remove(new_zip_latest_filename)
    shutil.copy(dest, new_zip_latest_filename)

    cons.print(f"New package moved to {frameworks_dir}")

    # cons.print("Updating platformio.ini")
    # platformio_ini = configparser.ConfigParser()
    # platformio_ini.read(platformio_ini_path)

    # # Update environments
    # for env in list(platformio_ini.values()):
    #     if env.get("platform") == "espressif32":
    #         platformio_ini.set(env.name, "platform_packages", f"{framework_name}@file://./src/frameworks/{os.path.basename(new_zip_filename)}")

    # with open(platformio_ini_path, 'w') as configfile:
    #     platformio_ini.write(configfile)
    # cons.print("platformio.ini updated.")

    update_environments.main(platformio_ini_path, do_all=True)

    cons.print("[green]Update complete![/green]")



if __name__ == "__main__":
    main()