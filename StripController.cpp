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

#include "StripController.h"

void StripController::init() {
    // Initialize the LED strip
    this->strip = LPD8806(LED_STRIP_LED_COUNT, LED_STRIP_PIN_DATA, LED_STRIP_PIN_CLOCK);

    // Begin the strip
    this->strip.begin();

    // Clear the LED strip
    this->clear();

    // Render the strip
    this->render();

    // Play the initialization animation
    animationInit();
}

LPD8806 StripController::getStrip() {
    return this->strip;
}

void StripController::clear() {
    // Loop through each LED, and clear it
    for(uint8_t i = 0; i < LED_STRIP_LED_COUNT; i++)
        this->strip.setPixelColor(i, 0);
}

void StripController::animationInit() {
    // Loop through each LED and render an animation
    for(uint8_t i = 0; i < LED_STRIP_LED_COUNT; i++) {
        // Light up the current LED
        strip.setPixelColor(i, strip.Color(127, 127, 127));

        // Clear the previous LED
        if(i > 0)
            this->strip.setPixelColor(i - 1, 0);

        // Render the strip
        this->render();
    }

    // Clear and render the strip
    this->clear();
    this->render();
}

bool StripController::stream() {
    // Loop through all LEDs
    for(uint8_t ledIndex = 0; ledIndex < LED_STRIP_LED_COUNT; ledIndex++) {
        // Create an array to read the color data into
        uint8_t colors[LED_STRIP_CHANNEL_COUNT];

        // Read the color data
        for(uint8_t i = 0; i < LED_STRIP_CHANNEL_COUNT; i++) {
            // Wait for data to be received
            // TODO: Add timeout
            while(!Serial.available());

            // Read the current color byte
            colors[i] = (uint8_t) Serial.read();

            // Stop if we're hitting a stream stop byte
            if(colors[i] == SwiftBoltProtocol::BYTE_STREAM_STOP) {
                // Render the current state of the strip
                this->render();

                // Return
                return false;
            }
        }

        // TODO: We should do this dynamically with the given number of color channels
        // Read the LED colors from the
        this->strip.setPixelColor(ledIndex, strip.Color(
                colors[0],
                colors[1],
                colors[2]
        ));

        // Delete the colors buffer
        delete[] colors;
    }

    // Render the LED strip
    this->render();

    // Read data until we've reached the stop bit for the stream
    // TODO: Add timeout
    while(((uint8_t) Serial.read()) != SwiftBoltProtocol::BYTE_STREAM_STOP);

    // Return
    return true;
}

void StripController::render() {
    this->strip.show();
}