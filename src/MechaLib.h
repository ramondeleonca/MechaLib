#pragma once
#ifndef MECHALIB_H
#define MECHALIB_H

//! Arduino core
#include <Arduino.h>

//! MechaLib modules
// Drive
#include <drive/ChassisSpeeds.h>
#include <drive/DifferentialDriveKinematics.h>
#include <drive/MecanumDriveKinematics.h>

// I2C
// Encoders
#include <i2c/encoder/ENCODER_I2C_AS5600.h>

// Multiplexers
#include <i2c/mux/I2C_MUX_Base.h>
#include <i2c/mux/I2C_MUX_TCA9548A.h>

// Motors
#include <motor/MOTOR_CONTROLLER_Base.h>
#include <motor/MOTOR_CONTROLLER_DRV8871.h>
#include <motor/MOTOR_CONTROLLER_L298N.h>
#include <motor/MotorSafety.h>

#endif