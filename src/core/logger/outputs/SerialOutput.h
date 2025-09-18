#pragma once
#ifndef SERIALOUTPUT_H
#define SERIALOUTPUT_H

#include <Arduino.h>

/**
 * ## SerialOutput
 * @brief [EN] Alias for Serial to be used as the default output stream for the `Logger`
 * @brief [ES] Alias para Serial que se usa como el output de salida default para el `Logger`
 */
Stream& SerialOutput = Serial;

#endif