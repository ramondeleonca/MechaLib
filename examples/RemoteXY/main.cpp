/**
 * @file main.cpp
 * @author Ramón de León (ramon@coahuilacreations.xyz)
 * @brief [EN] Example Robot using RemoteXY for wireless control.
 * @brief [ES] Ejemplo de robot que utiliza RemoteXY para control inalámbrico.
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 */

// [EN] Include Arduino core
// [ES] Incluir las funciones de Arduino
#include <Arduino.h>

// ! IMPORTANT / IMPORTANTE
// ! [EN] Include RemoteXY configuration (needs to be imported before MechaLib)
// ! [ES] Incluir la configuración de RemoteXY (necesita ser importada antes de MechaLib)
#include "./remotexy_conf.h"

// [EN] Include MechaLib
// [ES] Incluir MechaLib
#include <MechaLib.h>

/**
 * [EN] Define the Robot class extending RobotBase for the main robot code
 * RemoteXY handling is done automatically by MechaLib
 * 
 * [ES] Definir la clase Robot que extiende RobotBase para el código principal del robot
 * El manejo de RemoteXY se realiza automáticamente por MechaLib
 */
class Robot : public RobotBase {
    public:
        void robotSetup() override {
            Logger::getInstance().log("MechaLeague - RemoteXY Example");
        }

        void robotLoop() override {
            // Example: Log RemoteXY joystick values
            Logger::getInstance().log("Left Joystick: (" + String(RemoteXY.leftx) + ", " + String(RemoteXY.lefty) + ")");
            Logger::getInstance().log("Right Joystick: (" + String(RemoteXY.rightx) + ", " + String(RemoteXY.righty) + ")");
        }
};

// [EN] Create robot instance
// [ES] Crear instancia del robot
Robot robot;

// ! IMPORTANT / IMPORTANTE
/**
 * [EN] Register the robot instance so MechaLib can manage setup and loop calls automatically
 * [ES] Registrar la instancia del robot para que MechaLib pueda gestionar las llamadas de setup y loop automáticamente
 */
REGISTER_ROBOT(robot);