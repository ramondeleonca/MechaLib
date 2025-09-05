#pragma once
#ifndef MECHALIB_I2C_MUX_TCA9548A_H
#define MECHALIB_I2C_MUX_TCA9548A_H

#include <Arduino.h>
#include <TCA9548A.h>
#include <Wire.h>
#include <i2c/mux/I2C_MUX_Base.h>

class I2C_MUX_TCA9548A {
    private:
        TwoWire *wire;
        TCA9548A mux;
        const static uint8_t n_channels = 8;
        bool channelStates[n_channels] = {false};

        bool validateChannel(uint8_t channel) {
            if (channel >= n_channels - 1 || channel < 0)  {
                Serial.println("Invalid channel, must be between 0 and " + String(n_channels - 1));
                return false;
            }
            return true;
        }
    
    public:
        I2C_MUX_TCA9548A() {
            this->wire = &Wire;
            this->mux = TCA9548A();
        }

        I2C_MUX_TCA9548A(uint8_t address) {
            this->wire = &Wire;
            this->mux = TCA9548A(address);
        }

        I2C_MUX_TCA9548A(TwoWire *wire, uint8_t address) {
            this->wire = wire;
            this->mux = TCA9548A(address);  
        }

        /**
         * @brief Begin the I2C communication
         * By default this function begins the I2C bus,
         * if this behavior is not desired, pass false as the argument
         */
        void begin(bool beginI2C = true) {
            if (beginI2C) this->wire->begin();
            this->mux.begin(*this->wire);
        }

        /**
         * @brief Expose a channel to the I2C bus
         */
        bool exposeChannel(uint8_t channel) {
            if (!this->validateChannel(channel)) return false;
            this->mux.openChannel(channel);
            this->channelStates[channel] = true;
            return true;
        }

        /**
         * @brief Hide a channel from the I2C bus
         */
        bool hideChannel(uint8_t channel) {
            if (!this->validateChannel(channel)) return false;
            this->mux.closeChannel(channel);
            this->channelStates[channel] = false;
            return true;
        }

        /**
         * @brief Expose ALL channels to the I2C bus
         */
        void exposeAllChannels() {
            this->mux.openAll();
            for (uint8_t i = 0; i < n_channels; i++) this->channelStates[i] = true;
        }

        /**
         * @brief Hide ALL channels from the I2C bus
         */
        void hideAllChannels() {
            this->mux.closeAll();
            for (uint8_t i = 0; i < n_channels; i++) this->channelStates[i] = false;
        }

        /**
         * @brief Check if a channel is exposed
         */
        bool isChannelExposed(uint8_t channel) {
            if (!this->validateChannel(channel)) return false;
            return this->channelStates[channel];
        }

        /**
         * @brief Get the state of all channels
         */
        bool* getChannelStates() {
            return this->channelStates;
        }

        /**
         * @brief Write a raw value to the mux
         */
        void writeRawRegister(uint8_t value) {
            this->mux.writeRegister(value);
        }

        /**
         * @brief Read a raw value from the mux
         */
        byte readRawRegister() {
            return this->mux.readRegister();
        }

        ~I2C_MUX_TCA9548A() {
            this->mux.~TCA9548A();
        }
};

#endif