#pragma once
#ifndef BINDING_H
#define BINDING_H

#include <Arduino.h>
#include <type_traits>
#include <core/logic/EventLoop.h>

/**
 * ## Binding
 * @brief [EN] Class that represents a binding between a control input and a variable.
 * @brief [ES] Clase que representa una vinculación entre una entrada de control y una variable.
 * * This class is used to bind a control input (e.g., joystick, button) to a variable (e.g., motor speed, servo position).
 * Esta clase se utiliza para vincular una entrada de control (por ejemplo, joystick, botón) a una variable (por ejemplo, velocidad del motor, posición del servo).
 * * Supported types are `bool` and `float`.
 * Los tipos soportados son `bool` y `float`.
 */
template <typename T> class BindingBase {
    static_assert(std::is_same<T, bool> || std::is_same<T, float>, "Binding only supports bool and float types");

    protected:
        T (*provider)();

    public:
        BindingBase(T (*provider)()) : provider(provider) {}
        virtual ~BindingBase() = default;

        T get() const { return provider ? provider() : T{}; }
};

// Forward declaration of the Binding primary template
template <typename T> class Binding;

/**
 * Binding<bool>
 */
template <> class Binding<bool> : public BindingBase<bool> {
    public:
        using BindingBase<bool>::BindingBase; // inherit constructor

        /**
         * @brief [EN] Executes the action for every robot loop the binding is true.
         * @brief [ES] Ejecuta la acción en cada ciclo del robot mientras el binding sea verdadero.
         * * @param action [EN] Action to be executed.
         * [ES] Acción a ejecutar.
         */
        Binding<bool>& whileTrue(void (*action)()) {
            gamepadEventLoop.bind([this, action]() {
                if (this->get()) action();
            });
            return *this;
        }

        /**
         * @brief [EN] Executes the action for every robot loop the binding is false.
         * @brief [ES] Ejecuta la acción en cada ciclo del robot mientras el binding sea falso.
         * * @param action [EN] Action to be executed.
         * [ES] Acción a ejecutar.
         */
        Binding<bool>& whileFalse(void (*action)()) {
            gamepadEventLoop.bind([this, action]() {
                if (!this->get()) action();
            });
            return *this;
        }

        /**
         * @brief [EN] Executes the action when the binding changes from false to true.
         * @brief [ES] Ejecuta la acción cuando el binding cambia de falso a verdadero.
         * * @param action [EN] Action to be executed.
         * [ES] Acción a ejecutar.
         */
        Binding<bool>& onTrue(void (*action)()) {
            // Using a mutable lambda to store the last state, avoiding a static variable
            // that would be shared across all instances of Binding<bool>.
            auto eventHandler = [this, action, lastState = false]() mutable {
                bool currentState = this->get();
                if (currentState && !lastState) action();
                lastState = currentState;
            };
            gamepadEventLoop.bind(eventHandler);
            return *this;
        }

        /**
         * @brief [EN] Executes the action when the binding changes from true to false.
         * @brief [ES] Ejecuta la acción cuando el binding cambia de verdadero a falso.
         * * @param action [EN] Action to be executed.
         * [ES] Acción a ejecutar.
         */
        Binding<bool>& onFalse(void (*action)()) {
            // Using a mutable lambda to store the last state.
            auto eventHandler = [this, action, lastState = false]() mutable {
                bool currentState = this->get();
                if (!currentState && lastState) action();
                lastState = currentState;
            };
            gamepadEventLoop.bind(eventHandler);
            return *this;
        }
};

/**
 * Binding<float>
 */
template <> class Binding<float> : public BindingBase<float> {
    public:
        using BindingBase<float>::BindingBase; // inherit constructor

        /**
         * @brief [EN] Returns a binding that is true when the value is greater than the threshold.
         * @brief [ES] Devuelve un binding que es verdadero cuando el valor es mayor que el umbral.
         * * @param threshold 
         * @return Binding<bool> 
         */
        Binding<bool> greaterThan(float threshold) {
            return Binding<bool>([this, threshold]() {
                return this->get() > threshold;
            });
        }

        /**
         * @brief [EN] Returns a binding that is true when the value is less than the threshold.
         * @brief [ES] Devuelve un binding que es verdadero cuando el valor es menor que el umbral.
         * * @param threshold 
         * @return Binding<bool> 
         */        
        Binding<bool> lessThan(float threshold) {
            return Binding<bool>([this, threshold]() {
                return this->get() < threshold;
            });
        }
};

#endif