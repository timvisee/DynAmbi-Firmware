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

#ifndef DYNAMBI_TIMER_H
#define DYNAMBI_TIMER_H

#include <Arduino.h>

/**
 * Timer class.
 */
class Timer {
private:
    /**
     * Timeout delay in milliseconds.
     * */
    int timeoutDelay;

    /**
     * Timeout as time in milliseconds, represents millis() value.
     * */
    long timeout;

public:
    /**
     * Constructor.
     */
    Timer();

    /**
     * Constructor.
     *
     * @param timeout Timeout in milliseconds.
     */
    Timer(int timeout);

    /**
     * Constructor.
     *
     * @param timeout Timeout in milliseconds.
     * @param start True to immediately start the timer, false if not.
     */
    Timer(int timeout, bool start);

    /**
     * Get the timeout delay in milliseconds.
     *
     * @return Timeout delay.
     */
    int getTimeoutDelay();

    /**
     * Set the timeout delay in milliseconds.
     *
     * @return Timeout delay.
     */
    void setTimeoutDelay(int timeout);

    /**
     * Start the timer.
     */
    void start();

    /**
     * Start the timer with the specified delay in milliseconds.
     * This also updates the default delay of this timer.
     */
    void start(int timeoutDelay);

    /**
     * Check whether the timer is finished.
     *
     * @return True if finished, false if not.
     */
    bool isFinished();

    /**
     * Stop the timer if it's currently active.
     */
    void stop();
};

#endif //DYNAMBI_TIMER_H
