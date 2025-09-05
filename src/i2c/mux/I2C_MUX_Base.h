#pragma once
#ifndef MECHALIB_I2C_MUX_BASE_H
#define MECHALIB_I2C_MUX_BASE_H

#include <Arduino.h>

class I2C_MUX_Base {
    public:
        virtual void begin() = 0;
        virtual void exposeChannel(uint8_t channel) = 0;
        virtual void hideChannel(uint8_t channel) = 0;
        virtual void exposeAllChannels() = 0;
        virtual void hideAllChannels() = 0;
        virtual bool isChannelExposed(uint8_t channel) = 0;
        virtual bool* getChannelStates(uint8_t channel) = 0;
};

#endif