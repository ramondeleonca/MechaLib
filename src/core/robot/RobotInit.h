#pragma once
#ifndef ROBOTINIT_H
#define ROBOTINIT_H

#include <MechaLib.h>
#include <Arduino.h>

void setup() {
    #ifndef ROBOT_CLASS
    #error "ROBOT_CLASS is not defined"
    #endif
}

void loop() {

}

#endif