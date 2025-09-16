#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <drive/ChassisSpeeds.h>

class Logger {
    public:
        const int SERIAL_BAUD = 115200;
        
    private:
        Logger() {
            Serial.begin(SERIAL_BAUD);
        }
    
    public:
        void log(String message) {
            Serial.println(message);
        }

        void log(ChassisSpeeds &speeds) {
            Serial.println(speeds.toString());
        }

    // Singleton
    public:
        static Logger& getInstance() {
            static Logger instance;
            return instance;
        }
};

#endif