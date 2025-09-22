#pragma once
#ifndef MECHALIB_H
#define MECHALIB_H

//! Arduino core
#include <Arduino.h>

//! RemoteXY
#ifdef RemoteXY_CONF

#include <RemoteXY.h>

// TODO: Implement RemoteXY unsupported wifi logic
#ifdef REMOTEXY_MODE__WIFI_POINT && !defined(MECHALIB_REMOTEXY_ALLOW_WIFI_POINT)
#error "RemoteXY WiFi Point mode cannot be used in MechaLib"
#endif

#endif

//! MechaLib modules
// * Core
#include <core/logger/Logger.h>
#include <core/RobotBase.h>
#include <core/comms/comms.h>
#include <core/game/Alliance.h>

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