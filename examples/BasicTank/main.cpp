/**
 * @file main.cpp
 * @author Ramón de León (ramon@coahuilacreations.xyz)
 * @brief [EN] Example Robot using RemoteXY for wireless control of a tank drive.
 * @brief [ES] Ejemplo de robot que utiliza RemoteXY para control inalámbrico de un chasis de tanque.
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

// [EN] Create motor objects
// [ES] Crear objetos de motor
MOTOR_CONTROLLER_L298N leftMotor(22, 23, 2);
MOTOR_CONTROLLER_L298N rightMotor(32, 33, 15);

// [EN] Create chassis speeds object
// [ES] Crear objeto de velocidades del chasis
ChassisSpeeds chassisSpeeds;

// [EN] Create kinematics object
// [ES] Crear objeto de cinemática
float wheelSpeeds[2];
DifferentialDriveKinematics driveKinematics(0.2, 0.06);

class Robot : public RobotBase {
    public:
        void robotSetup() override {
            Logger::getInstance().log("Robot setup.");
        }

        void robotLoop() override {
            // TODO: Comment and check
            chassisSpeeds.set(0.0, RemoteXY.lefty / 100, RemoteXY.rightx / 100);
            driveKinematics.calculateWheelSpeeds(wheelSpeeds, chassisSpeeds.getVy(), chassisSpeeds.getOmega());
            DifferentialDriveKinematics::normalizeWheelSpeeds(wheelSpeeds);
            leftMotor.set(wheelSpeeds[0]);
            rightMotor.set(wheelSpeeds[1]);
        }
};

// Create robot instance
Robot robot;

// Register robot
REGISTER_ROBOT(robot);