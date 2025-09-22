#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <drive/ChassisSpeeds.h>

/**
 * ## Logger
 * @brief [EN] Logger for logging messages to Serial and telemetry with different log levels.
 * @brief [ES] Logger para registrar mensajes en Serial y telemetría con diferentes niveles de gravedad.
 */
class Logger {
    public:
        const int SERIAL_BAUD = 115200;

        enum LOG_LEVEL {
            NONE = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4
        };

        const char* LOG_LEVEL_PREFIXES[5] = {
            "",
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