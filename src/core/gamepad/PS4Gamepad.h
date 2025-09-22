#pragma once
#ifndef PS4_GAMEPAD_H
#define PS4_GAMEPAD_H

#define NO_GLOBAL_INSTANCES
#include <PS4Controller.h>

#include <Arduino.h>
#include <core/gamepad/Binding.h>

/**
 * ## PS4Gamepad
 * @brief [EN] PS4 Gamepad handler
 * @brief [ES] Manejador de gamepad PS4
 */
class PS4Gamepad {
    private:
        PS4Controller* gamepad;

    public:
        /**
         * @brief [EN] Construct a new PS4Gamepad object
         * @brief [ES] Construye un nuevo objeto PS4Gamepad
         * 
         * @param macAddress [EN] Gamepad bluetooth MAC address
         * [ES] Dirección MAC bluetooth del gamepad
         */
        PS4Gamepad(const char* macAddress) {
            // Create gamepad object
            this->gamepad = new PS4Controller();
            
            // Register callbacks
            
            // this->gamepad->attachOnConnect();
        }

        ~PS4Gamepad() {
            this->gamepad->end();
            delete this->gamepad;
        }
};

#endif
