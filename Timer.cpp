/******************************************************************************
 * Copyright (c) ArduinoDynambi 2016. All rights reserved.                    *
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

#include "Timer.h"

Timer::Timer() {
    // Set the timeout to it's default
    this->timeout = -1;

    // Set the timeout variable
    this->timeoutDelay = 1000;
}

Timer::Timer(int timeout) {
    // Set the timeout to it's default
    this->timeout = -1;

    // Set the timeout variable
    this->timeoutDelay = timeout;
}

Timer::Timer(int timeout, bool start) {
    // Set the timeout to it's default
    this->timeout = -1;

    // Set the timeout variable
    this->timeoutDelay = timeout;

    // Start the timer
    if(start)
        this->start();
}

int Timer::getTimeoutDelay() {
    return this->timeoutDelay;
}

void Timer::setTimeoutDelay(int timeout) {
    this->timeoutDelay = timeout;
}

void Timer::start() {
    this->start(this->getTimeoutDelay());
}

void Timer::start(int timeoutDelay) {
    // Set the timeout
    this->timeout = millis() + timeoutDelay;

    // Update the timeout delay
    this->timeoutDelay = timeoutDelay;
}

bool Timer::isFinished() {
    return this->timeout < millis() && this->timeout >= 0;
}

void Timer::stop() {
    this->timeout = -1;
}