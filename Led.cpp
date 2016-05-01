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

#include "Led.h"
#include "Globals.h"

const uint8_t Led::BRIGHTNESS_LOW = 0;
const uint8_t Led::BRIGHTNESS_HIGH = 255;
const uint8_t Led::STATUS_LED_PIN = 13;
const bool Led::STATUS_LED_ANALOG = false;

Led::Led() {
    this->pin = Led::STATUS_LED_PIN;
}

Led::Led(uint8_t pin, bool analogMode) {
    // Set the default variable values
    this->state = false;
    this->analogMode = analogMode;
    this->fadeDuration = 180;
    this->fromBrightness = 0;
    this->fromTime = -1;
    this->toBrightness = 0;
    this->toTime = -1;
    this->brightness = 0;
    this->pulsing = false;
    this->pulseMin = LEDCONTROLLER_PULSE_BRIGHTNESS_MIN;
    this->pulseMax = LEDCONTROLLER_PULSE_BRIGHTNESS_MAX;
    this->pulseDuration = LEDCONTROLLER_PULSE_DURATION;

    // Set the LED pin
    this->pin = pin;
}

void Led::setupPin() {
    pinMode(this->pin, OUTPUT);
}

uint8_t Led::getPin() {
    return this->pin;
}

bool Led::inAnalogMode() {
    return this->analogMode;
}

void Led::setAnalogMode(bool analogMode) {
    this->analogMode = analogMode;
}

int Led::getFadeDuration() {
    return this->fadeDuration;
}

void Led::setFadeDuration(int fadeDuration) {
    this->fadeDuration = fadeDuration;
}

void Led::update() {
    // Make sure the LED is analog
    if(!this->inAnalogMode()) {
        // Handle pulsing for non-analog LEDs
        if(this->isPulsing())
            // Determine and set the LED state
            this->setState(millis() % this->pulseDuration < this->pulseDuration / 2.0);

        // We're done, return
        return;
    }

    // Get the time delta
    unsigned long timeDelta = (unsigned long) (this->toTime - this->fromTime);

    // Get the brightness delta
    int brightnessDelta = this->toBrightness - this->fromBrightness;

    // Calculate the delta position
    int timeDeltaPos = (int) min(max(millis() - this->fromTime, 0), timeDelta);

    // Calculate the current time factor
    float factor = (float) timeDeltaPos / (float) timeDelta;

    // Determine the brightness value
    uint8_t brightness = (uint8_t) (this->fromBrightness + (brightnessDelta * factor));

    // Handle pulsing
    if(this->pulsing && !isFading()) {
        // Calculate the pulse delta
        int pulseBrightnessDelta = this->pulseMax - this->pulseMin;

        // Calculate the time part
        double timePart = millis() % this->pulseDuration;

        // Properly determine the time part when fading out
        if(timePart > this->pulseDuration / 2)
            timePart = (timePart - this->pulseDuration) * -1;

        // Calculate and set the brightness
        brightness = (uint8_t)
                (((double) this->pulseMin + pulseBrightnessDelta)
                 * (timePart / (this->pulseDuration / 2.0)));
    }

    // Set the brightness of the led
    this->setBrightness(brightness);
}

bool Led::getState() {
    return this->state;
}

void Led::setState(bool state) {
    // Set the state
    this->state = state;

    // Update the LED
    if(this->inAnalogMode())
        this->fade(state ? BRIGHTNESS_HIGH : BRIGHTNESS_LOW);
    else
        digitalWrite(this->pin, state ? HIGH : LOW);
}

void Led::fade(uint8_t brightness) {
    this->fade(brightness, this->getFadeDuration());
}

void Led::fade(uint8_t brightness, int duration) {
    // Set the animation variables
    this->fromBrightness = this->getBrightness();
    this->toBrightness = brightness;
    this->fromTime = millis();
    this->toTime = millis() + duration;

    // Update
    this->update();

    // Update the state flag
    this->state = ((double) brightness / (double) (BRIGHTNESS_HIGH - BRIGHTNESS_LOW)) >= 0.5;
}

bool Led::isFading() {
    return (this->toTime > millis() && this->brightness != this->toBrightness && this->toTime >= 0);
}

uint8_t Led::getBrightness() {
    return this->brightness;
}

void Led::setBrightness(uint8_t brightness) {
    // Store the brightness
    this->brightness = brightness;

    // Set the actual brightness
    if(this->inAnalogMode())
        analogWrite(this->pin, brightness);
    else
        digitalWrite(this->pin, brightness >= 256 / 2 ? HIGH : LOW);
}

uint8_t Led::getToBrightness() {
    return this->toBrightness;
}

int Led::getFadeTimeLeft() {
    return (int) (this->toTime - millis());
}
bool Led::isPulsing() {
    return this->pulsing;
}

void Led::setPulsing(bool pulsing) {
    // Determine whether the pulsing state changed
    const bool changed = this->pulsing != pulsing;

    // Set the pulsing flag
    this->pulsing = pulsing;

    // Properly fade into pulsing mode
    if(changed && pulsing) {

        // Fade the LED to it's pulse state if it's in analog mode
        if(this->inAnalogMode()) {
            // Determine the remaining pulse time
            int pulseTimeRemaining = (int) (this->pulseDuration - (millis() % this->pulseDuration));

            // Fade to the nearest pulse brightness bound
            if(pulseTimeRemaining < this->pulseDuration / 2)
                this->fade(this->pulseMin, pulseTimeRemaining);
            else
                this->fade(this->pulseMax, pulseTimeRemaining - (this->pulseDuration / 2));
        }

        // Force-update
        this->update();
    }
}

uint8_t Led::getPulseMinimum() {
    return this->pulseMin;
}

void Led::setPulseMinimum(uint8_t pulseMin) {
    this->pulseMin = pulseMin;
}

uint8_t Led::getPulseMaximum() {
    return this->pulseMin;
}

void Led::setPulseMaximum(uint8_t pulseMax) {
    this->pulseMax = pulseMax;
}

int Led::getPulseDuration() {
    return this->pulseDuration;
}

void Led::setPulseDuration(int duration) {
    this->pulseDuration = duration;
}

int Led::calculatePulseDuration(int from, int to) {
    // Calculate the delta value
    double brightnessDelta = max(from, to) - min(from, to);

    // Calculate the pulse brightness delta
    double pulseBrightnessDelta = this->pulseMax - this->pulseMin;

    // Calculate the time factor for the pulse brightness delta
    double factor = brightnessDelta / pulseBrightnessDelta;

    // Calculate and return the duration for the specified fade distance
    return (int) (this->pulseDuration * factor / 2.0);
}
