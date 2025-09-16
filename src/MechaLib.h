#pragma once
#ifndef MECHALIB_H
#define MECHALIB_H

//! Arduino core
#include <Arduino.h>

//! Bluepad
// #include <Bluepad32.h>

//! RemoteXY
#include <RemoteXY.h>

//! MechaLib modules
// * Core
#include <core/Logger.h>
#include <core/RobotBase.h>

//* Drive
#include <drive/ChassisSpeeds.h>
#include <drive/DifferentialDriveKinematics.h>
#include <drive/MecanumDriveKinematics.h>

//* I2C
// Encoders
#include <i2c/encoder/ENCODER_I2C_AS5600.h>

//* Multiplexers
#include <i2c/mux/I2C_MUX_Base.h>
#include <i2c/mux/I2C_MUX_TCA9548A.h>

//* Motors
#include <motor/MotorSafety.h>

// DC Motors
#include <motor/dc/MOTOR_CONTROLLER_Base.h>
#include <motor/dc/MOTOR_CONTROLLER_DRV8871.h>
#include <motor/dc/MOTOR_CONTROLLER_L298N.h>

// Servo Motors
#include <motor/servo/SERVO_Base.h>

#endif