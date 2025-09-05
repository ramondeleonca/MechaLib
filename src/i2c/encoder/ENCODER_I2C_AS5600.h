#pragma once
#ifndef MECHALIB_ENCODER_I2C_AS5600_H
#define MECHALIB_ENCODER_I2C_AS5600_H

#include <Arduino.h>
#include <Wire.h>
#include <AS5600.h>

class ENCODER_AS5600 {
    private:
        TwoWire *wire;
        AS5600 encoder;
        int8_t directionPin = -1;

    public:
        // ENCODER_AS5600(TwoWire *wire = &Wire) {
        //     this->wire = wire;
        //     encoder = AS5600();
        // }

        // ENCODER_AS5600(TwoWire *wire, uint8_t directionPin) {
        //     this->wire = wire;
        //     this->directionPin = directionPin;
        //     encoder = AS5600();
        // }

        // ENCODER_AS5600(uint8_t directionPin) {
        //     this->wire = &Wire;
        //     this->directionPin = directionPin;
        //     encoder = AS5600();
        // }

        ENCODER_AS5600() {
            this->wire = &Wire;
            encoder = AS5600(this->wire);
        }

        /**
         * @brief Begin the I2C communication
         * By default this function begins the I2C bus,
         * if this behavior is not desired, pass false as the argument
         */
        void begin(bool beginI2C = true) {
            if (beginI2C) this->wire->begin();
            if (this->directionPin != -1) {
                encoder.begin(this->directionPin);
            } else {
                encoder.begin();
            }
        }

        uint16_t getAbsoluteAngle() {
            return encoder.rawAngle();
        }
};

#endif