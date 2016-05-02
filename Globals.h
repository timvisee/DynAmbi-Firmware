/******************************************************************************
 * Copyright (c) ArduinoDynAmbi 2016. All rights reserved.                    *
 *                                                                            *
 * @author Tim Visee                                                          *
 * @website http://timvisee.com/                                              *
 *                                                                            *
 * Open Source != No Copyright                                                *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included    *
 * in all copies or substantial portions of the Software.                     *
 *                                                                            *
 * You should have received a copy of The MIT License (MIT) along with this   *
 * program. If not, see <http://opensource.org/licenses/MIT/>.                *
 ******************************************************************************/

#ifndef DYNAMBI_GLOBALS_H
#define DYNAMBI_GLOBALS_H

#include <Arduino.h>

/**
 * Debug mode.
 * True to enable, false to disable.
 */
const bool DEBUG = true;



/**
 * LED strip configuration.
 */

/**
 * Number of LEDs on the strip.
 */
const uint8_t LED_STRIP_LED_COUNT = 62;

/**
 * Number of color channels on the LED strip.
 */
const uint8_t LED_STRIP_CHANNEL_COUNT = 3;



/**
 * LED controller configuration.
 */

/**
 * Defines the minimum brightness of a pulse.
 */
const uint8_t LEDCONTROLLER_PULSE_BRIGHTNESS_MIN = 30;

/**
 * Defines the maximum brightness of a pulse.
 */
const uint8_t LEDCONTROLLER_PULSE_BRIGHTNESS_MAX = 80;

/**
 * Defines the pulse duration.
 */
const int LEDCONTROLLER_PULSE_DURATION = 750;



/**
 * Connection configuration.
 */

/**
 * Define whether the serial USB connection is enabled.
 */
const int SERIAL_USB_ENABLED = true;

/**
 * The USB serial baud rate.
 */
const int SERIAL_USB_BAUD = 115200;

#endif //DYNAMBI_GLOBALS_H
