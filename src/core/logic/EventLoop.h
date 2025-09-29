#pragma once
#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <core/logger/Logger.h>

/**
 * ## EventLoop
 * @brief [EN] Class that represents an event loop.
 * @brief [ES] Clase que representa un bucle de eventos.
 */
template <uint8_t MAX_CALLBACKS = 32> class EventLoop {
    private:
        void (*callbacks[MAX_CALLBACKS])();
        uint8_t callbackCount = 0;
        const char* name;

    public:
        /**
         * @brief [EN] Constructs an EventLoop with an optional name.
         * @brief [ES] Construye un EventLoop con un nombre opcional.
         * 
         * @param name Name of the event loop.
         */
        EventLoop(const char* name = "EventLoop") {
            this->name = name;
        }

        /**
         * @brief [EN] Binds a callback to be called on each poll.
         * @brief [ES] Vincula una función para ser llamada en cada llamada.
         * 
         * @param callback Function to be called.
         */
        void bind(void (*callback)()) {
            if (callbackCount < MAX_CALLBACKS) {
                callbacks[callbackCount++] = callback;
            } else {
                Logger::getInstance().log(F("EventLoop: Maximum number of callbacks reached: "), Logger::LOG_LEVEL::ERROR, false);
                Logger::getInstance().log(name, Logger::LOG_LEVEL::NONE);
            }
        }

        /**
         * @brief [EN] Binds a callback to be called only once on the next poll.
         * @brief [ES] Vincula una función para ser llamada solo una vez en la siguiente llamada.
         * 
         * @param callback Function to be called once.
         */
        void bindOnce(void (*callback)()) {
            // Wrap the callback to unbind itself after being called
            this->bind(callbacks[callbackCount++] = [this, callback]() {
                callback();
                this->unbind(callback);
            });
        }

        /**
         * @brief [EN] Binds a callback to be called only once after the delay time has passed (non-blocking).
         * @brief [ES] Vincula una función para ser llamada solo una vez cuando el tiempo de delay haya pasado (no bloquea).
         * 
         * @param callback Function to be called once.
         * @param delayMs Time to pass before calling
         */
        void bindOnceDelay(void (*callback)(), uint16_t delayMs) {
            static uint32_t bindTime = millis();
            // Wrap the callback to unbind itself after being called after the time specified
            this->bind(callbacks[callbackCount++] = [this, callback]() {
                if (millis() >= bindTime + delayMs) {
                    callback();
                    this->unbind(callback);
                }
            });
        }

        /**
         * @brief [EN] Unbinds all callbacks.
         * @brief [ES] Desvincula todas las funciones.
         */
        void unbindAll() {
            for (uint8_t i = 0; i < callbackCount; i++) callbacks[i] = nullptr;
            callbackCount = 0;
        }

        /**
         * @brief [EN] Unbinds a specific callback.
         * @brief [ES] Desvincula una función específica.
         * 
         * @param callback Function to be unbound.
         */
        void unbind(void (*callback)()) {
            for (uint8_t i = 0; i < callbackCount; i++) {
                if (callbacks[i] == callback) {
                    callbacks[i] = nullptr;
                    // Shift remaining callbacks
                    for (uint8_t j = i; j < callbackCount - 1; j++) callbacks[j] = callbacks[j + 1];
                    callbacks[--callbackCount] = nullptr;
                    break;
                }
            }
        }

        /**
         * @brief [EN] Polls all bound callbacks.
         * @brief [ES] Llama todas las funciones vinculadas.
         */
        void poll() {
            for (uint8_t i = 0; i < callbackCount; i++) if (callbacks[i]) callbacks[i]();
        }
};

/**
 * ## gamepadEventLoop
 * @brief [EN] Static instance of EventLoop for gamepad polling.
 * @brief [ES] Instancia estática de EventLoop para el sondeo del gamepad.
 */
EventLoop<64> gamepadEventLoop("GamepadEventLoop");

/**
 * ## defaultEventLoop
 * @brief [EN] Static instance of EventLoop for general purposes.
 * @brief [ES] Instancia estática de EventLoop para propósitos generales.
 */
EventLoop<32> defaultEventLoop("DefaultEventLoop");

#endif