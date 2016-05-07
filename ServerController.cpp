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

#include "ServerController.h"

// Initialize fields
EthernetServer ServerController::server = NULL;
bool ServerController::started = false;
EthernetClient ServerController::client = NULL;
bool ServerController::clientConnected = false;

EthernetServer ServerController::getServer() {
    return ServerController::server;
}

void ServerController::start() {
    // Set up the Ethernet server.
    // TODO: Use configurable port!
    ServerController::server = EthernetServer(23);

    // Set the started flag
    ServerController::started = true;
}

bool ServerController::isStarted() {
    return ServerController::started;
}

void ServerController::stop() {
    // Make sure the server is started
    if(!ServerController::isStarted())
        return;

    // Delete the server instance, and reset it afterwards
    // TODO: Check this statement!
    delete &ServerController::server;
    ServerController::server = NULL;

    // Reset the started flag
    ServerController::started = false;
}

void ServerController::update() {
    // Disconnect from the client if the connection dropped
    if(ServerController::clientConnected && !ServerController::client.connected()) {
        Serial.println("DISCONNECTING");
        // Stop the connection
        ServerController::client.stop();

        // Reset the connection
        ServerController::client = NULL;
        ServerController::clientConnected = false;

        // Show a status message
        Serial.println("Client disconnected.");
    }

    // Check if a new client is available if none is connected
    if(!ServerController::isClientConnected()) {
        // TODO: Check if a client is available!

        // Get the current available client status
        ServerController::client = ServerController::server.available();

        // Do not connect if this isn't a valid client
        if(!ServerController::client || !ServerController::client.connected()) {
            // Reset the client and return
            ServerController::client = NULL;
            return;
        }

        // Set the client's connection status
        ServerController::clientConnected = true;

        // Clear the input buffer before we're starting
        //ServerController::client.flush();

        // Set the connection timeout
        // TODO: Make timeout configurable!
        ServerController::client.setTimeout(5000);

        // Show a status message
        Serial.println("Client connected.");
    }
}

EthernetClient ServerController::getClient() {
    return ServerController::client;
}

bool ServerController::isClientConnected() {
    return ServerController::clientConnected && ServerController::client.connected();
}
