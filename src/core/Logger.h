#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

const int LOGGER_SERIAL_BAUD = 115200;

class Logger {
    private:
        Logger() {
            Serial.begin(LOGGER_SERIAL_BAUD);
            
        }

    // Singleton
    public:
        static Logger& getInstance() {
            static Logger instance;
            return instance;
        }
};

#endif