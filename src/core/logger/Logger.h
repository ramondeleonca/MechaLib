#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <drive/ChassisSpeeds.h>

class Logger {
    public:
        const int SERIAL_BAUD = 115200;

        enum LOG_LEVEL {
            DEBUG = 0,
            INFO = 1,
            WARN = 2,
            ERROR = 3
        };

        const char* LOG_LEVEL_PREFIXES[4] = {
            "[DEBUG] ",
            "[INFO] ",
            "[WARN] ",
            "[ERROR] "
        };
        
    private:
        Logger() {
            Serial.begin(SERIAL_BAUD);
        }
    
    public:
        void log(String message, LOG_LEVEL level = INFO, bool newline = true) {
            Serial.print(LOG_LEVEL_PREFIXES[level]);
            Serial.print(message);
            if (newline) Serial.println();
        }

        void log(ChassisSpeeds &speeds) {
            log(speeds.toString());
        }

    // Singleton
    public:
        static Logger& getInstance() {
            static Logger instance;
            return instance;
        }
};

#endif