#pragma once
#ifndef BINDING_H
#define BINDING_H

#include <Arduino.h>
#include <type_traits>

/**
 * ## Binding
 * @brief [EN] Class that represents a binding between a control input and a variable.
 * @brief [ES] Clase que representa una vinculación entre una entrada de control y una variable.
 * 
 * This class is used to bind a control input (e.g., joystick, button) to a variable (e.g., motor speed, servo position).
 * Esta clase se utiliza para vincular una entrada de control (por ejemplo, joystick, botón) a una variable (por ejemplo, velocidad del motor, posición del servo).
 * 
 * Supported types are `bool` and `float`.
 * Los tipos soportados son `bool` y `float`.
 * 
 * Example:
 * ```cpp
 * Binding<float> leftJoystickX;
 * Binding<bool> buttonA;
 * ```
 */
template <typename T> class Binding {
    static_assert(std::is_same<T, bool> || std::is_same<T, float>, "Binding only supports bool and float types");

    protected:
        T (*provider)();

    public:
        Binding(T (*provider)()) {
            this->provider = provider;
        }

};

template <> class Binding<bool> {

}

template <> class Binding<float> {
    public:
        Binding<bool> greaterThan(float threshold) {
            
            return Binding<bool>([]() {
                return 
            });
        }
}

#endif