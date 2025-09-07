import configparser
import sys
import rich.console
import os

cons = rich.console.Console()
zip_name = "framework-arduinoespressif32-bluepad32-latest.zip"
framework_name = "framework-arduinoespressif32"

def main(platformio_ini_path, do_all=False):
    cons.print("Updating platformio.ini")
    platformio_ini = configparser.ConfigParser()
    platformio_ini.read(platformio_ini_path)

    # Update environments
    for env in list(platformio_ini.values()):
        if env.get("platform") == "espressif32" and ("MechaLib" in env.get("lib_deps") or do_all):
            platformio_ini.set(env.name, "platform_packages", f"{framework_name}@file://./src/frameworks/{zip_name}")

    with open(platformio_ini_path, 'w') as configfile:
        platformio_ini.write(configfile)
    cons.print("platformio.ini updated.")

if __name__ == "__main__":
    conf_path = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.getcwd(), "platformio.ini")
    main(conf_path, do_all="--all" in sys.argv)