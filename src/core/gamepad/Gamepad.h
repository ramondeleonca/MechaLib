#pragma once
#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Arduino.h>
#include <Bluepad32.h>

/**
 * Gamepad Manager
 * Supported gamepads: https://bluepad32.readthedocs.io/en/latest/supported_gamepads/
 */
class GamepadManager {
    private:
        static GamepadPtr gamepads[2];

        void onConnect() {

        };

        void onDisconnect() {

        };

    public:
        GamepadManager() {
            // TODO: Make it so it is only enabled when the robot is in dev mode
            BP32.enableBLEService(true);
            BP32.enableNewBluetoothConnections(true);
            
            const ControllerCallback onConnect = [](ControllerPtr gp) {

            };

            const ControllerCallback onDisconnect = [](ControllerPtr gp) {

            };

            BP32.setup(onConnect, onDisconnect);
        };

    // Singleton
    public:
        static GamepadManager& getInstance() {
            static GamepadManager instance;
            return instance;
        }
};

#endif