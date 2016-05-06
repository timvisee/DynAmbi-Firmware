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

#ifndef DYNAMBI_CORE_H
#define DYNAMBI_CORE_H

#include <Arduino.h>
#include "Globals.h"
#include "Led.h"
#include "LedManager.h"
#include "StripController.h"

#include "ServerController.h"

#include <SPI.h>
#include <Ethernet.h>

/**
 * Core class.
 */
class Core {
private:
    /**
     * Flag whether the device has been fully started or not.
     */
    bool started;

    /**
     * LED strip controller instance.
     */
    StripController strip;

public:
    /**
     * Constructor.
     */
    Core();

    /**
     * Called once on set up.
     */
    void setup();

private:
    /**
     * Set up the serial subsystem.
     */
    void setupSerial();

    /**
     * Set up the ethernet subsystem.
     */
    void setupEthernet();

public:
    /**
     * Called each loop.
     */
    void loop();

    /**
     * Method used to update all internal logic.
     */
    void updateLogic();

    /**
     * A smart delay method.
     * This method is similar to Arduino's delay method, but it keeps calling the update() method while the delay method is executed instead of freezing the Arduino.
     *
     * @param delay The delay in milliseconds to wait.
     */
    void smartDelay(int delay);
};

#endif //DYNAMBI_CORE_H
