#pragma once
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

enum class MT1_MessageType : uint8_t {
    SET,
    DEL,
    SYNC,
    PING
};

enum class MT1_ValueType : uint8_t {
    FLOAT,
    STRING,
    BOOL
};

#pragma pack(push, 1)
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

MT1_Message msg;

void setup() {
    
}

#endif
