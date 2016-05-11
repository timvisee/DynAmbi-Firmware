/******************************************************************************
 * Copyright (c) DynAmbi-Firmware 2016. All rights reserved.                  *
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
 * General configuration.
 */

/**
 * Device name.
 */
#define DEVICE_NAME "DynAmbi Controller"

/**
 * Device version.
 */
#define DEVICE_VERSION_NAME "0.1"

/**
 * Debug mode.
 * True to enable, false to disable.
 */
#define DEBUG true

/**
 * Memory report interval in milliseconds.
 */
#define MEMORY_REPORT_INTERVAL 5000



/**
 * Ethernet configuration.
 */

/**
 * Ethernet shield MAC address.
 */
const uint8_t ETHERNET_MAC[] = {
        0x90, 0xA2, 0xDA, 0x0D, 0x01, 0x44
};

/**
 * Ethernet host name.
 */
#define ETHERNET_HOST_NAME "DynAmbi"



/**
 * LED configuration.
 */

/**
 * Error LED pin.
 */
#define ERROR_LED_PIN 6

/**
 * Error LED analog mode.
 */
#define ERROR_LED_ANALOG true

/**
 * Status LED pin.
 */
#define STATUS_LED_PIN 5

/**
 * Status LED analog mode.
 */
#define STATUS_LED_ANALOG true



/**
 * LED strip configuration.
 */

/**
 * Data pin for the LED strip.
 */
#define LED_STRIP_PIN_DATA 2

/**
 * Clock pin for the LED strip.
 */
#define LED_STRIP_PIN_CLOCK 3

/**
 * Number of LEDs on the strip.
 */
#define LED_STRIP_LED_COUNT 62

/**
 * Number of color channels on the LED strip.
 */
#define LED_STRIP_CHANNEL_COUNT 3



/**
 * LED controller configuration.
 */

/**
 * Defines the minimum brightness of a pulse.
 */
#define LEDCONTROLLER_PULSE_BRIGHTNESS_MIN 30

/**
 * Defines the maximum brightness of a pulse.
 */
#define LEDCONTROLLER_PULSE_BRIGHTNESS_MAX 80

/**
 * Defines the pulse duration.
 */
#define LEDCONTROLLER_PULSE_DURATION 750



/**
 * Connection configuration.
 */

/**
 * Define whether the serial USB connection is enabled.
 */
#define SERIAL_USB_ENABLED true

/**
 * The USB serial baud rate.
 */
#define SERIAL_USB_BAUD 115200

#endif //DYNAMBI_GLOBALS_H
