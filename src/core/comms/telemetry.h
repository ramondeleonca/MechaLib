#pragma once
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

/**
 * @brief [EN] MechaTelemetry1 Message Types
 * @brief [ES] Tipos de Mensajes de MechaTelemetry1
 */
enum class MT1_MessageType : uint8_t {
    SET = 0,
    DEL = 1,
    SYNC = 2,
    PING = 3
};

/**
 * @brief [EN] MechaTelemetry1 Value Types
 * @brief [ES] Tipos de Valores de MechaTelemetry1
 */
enum class MT1_ValueType : uint8_t {
    FLOAT,
    STRING,
    BOOL
};

#pragma pack(push, 1)
/**
 * @brief [EN] MechaTelemetry1 Message Structure
 * @brief [ES] Estructura de Mensaje de MechaTelemetry1
 */
struct MT1_Message {
    MT1_MessageType messageType;
    MT1_ValueType valueType;

    uint8_t keyLength;
    uint8_t valueLength;

    // TODO: Add key and value handling
    union {
        float floatValue;
        const char* stringValue;
        bool boolValue;
    } value;
};
#pragma pack(pop)

#endif
