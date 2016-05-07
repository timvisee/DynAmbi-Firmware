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

    // TODO: Stop the server!

    // Reset the started flag
    ServerController::started = false;
}