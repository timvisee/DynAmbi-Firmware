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

#ifndef DYNAMBI_CONNECTIONMANAGER_H
#define DYNAMBI_CONNECTIONMANAGER_H

#include <SPI.h>
#include <Ethernet.h>

class ServerController {
private:
    /**
     * Server instance.
     */
    static EthernetServer server;

    /**
     * Flag to define whether the server is started.
     */
    static bool started;

    /**
     * A connected ethernet client.
     */
    static EthernetClient client;

    /**
     * Flag to define whether a client is connected or not.
     */
    static bool clientConnected;

public:
    /**
     * Get the server instance.
     */
    static EthernetServer getServer();

    /**
     * Start and set up the server.
     * This method call will be ignored if the server is started already.
     */
    static void start();

    /**
     * Check whether the server is started.
     */
    static bool isStarted();

    /**
     * Stop the server if it's currently running.
     */
    static void stop();

    /**
     * Update the connection status.
     */
    static void update();

    /**
     * Get the connected client.
     */
    static EthernetClient getClient();

    /**
     * Check whether a client is connected.
     */
    static bool isClientConnected();
};

#endif //DYNAMBI_CONNECTIONMANAGER_H
