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

#include "Core.h"
#include "Random.h"
#include "Timer.h"

Core::Core() {
    // Field initialization
    this->started = false;
    this->strip = StripController();
}

void Core::setup() {
    // Set up the serial connection
    setupSerial();

    // Show a status message
    Serial.print("Starting ");
    Serial.print(DEVICE_NAME);
    Serial.print(" v");
    Serial.print(DEVICE_VERSION_NAME);
    Serial.println("...");

    // Randomize the random seed
    Random::randomize();

    // Set up the LED manager
    LedManager::setup();

    // Enable pulsing for the status LED
    LedManager::statusLed.setPulsing(true);

    // Initialize the LED strip
    this->strip.init();

    // Set up the ethernet subsystem
    setupEthernet();

    // Set up and start the server
    ServerController::start();

    // The device has been started, update the flag
    this->started = true;

    // Wait for a client to connect
    do
        updateLogic();
    while(!ServerController::isClientConnected());

    // Wait for a connection
    // TODO: Replace this with proper handshaking!
    while(!ServerController::getClient().available() || ServerController::getClient().read() != 'o')
        updateLogic();
    while(!ServerController::getClient().available() || ServerController::getClient().read() != 'z')
        updateLogic();

    // Show the connection animator
    this->strip.animationConnect();
}

void Core::setupSerial() {
    // Enable the serial connection
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
    if(SERIAL_USB_ENABLED) {
        // Begin the serial connection
        Serial.begin(SERIAL_USB_BAUD);

        // Wait for the serial connection to become available
        while(!Serial);
    }
#pragma clang diagnostic pop
}

void Core::setupEthernet() {
    // Show a status message
    Serial.println("Setting up Ethernet connection...");

    // Define the preferred DHCP hostname
    Ethernet.hostName(ETHERNET_HOST_NAME);

    // Start the ethernet connection and request an IP address using DHCP
    if(Ethernet.begin((uint8_t *) ETHERNET_MAC) == 0) {
        // Show a status message
        Serial.println("ERR: Failed to request IP address using DHCP");

        // Enable the error LED
        LedManager::errorLed.setState(true);

        // Unable to continue, keep looping the logic loop
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
        while(true)
            updateLogic();
#pragma clang diagnostic pop
    }

    // Print the local IP address
    Serial.print("IP address: ");
    for(byte thisByte = 0; thisByte < 4; thisByte++) {
        // Print the number bit
        Serial.print(Ethernet.localIP()[thisByte], DEC);

        // Print the separator or new line
        if(thisByte < 3)
            Serial.print(".");
        else
            Serial.println();
    }

    // Print the hostname
    Serial.print("Host name: ");
    Serial.println(Ethernet.getHostName());
}

void Core::loop() {
    // Update the server controller
    ServerController::update();

    // Check whether a client is connected
    if(ServerController::isClientConnected()) {
        // TODO: Debug message
        Serial.println("CONNECTED! ");

        // Read incoming data once available
        if(ServerController::getClient().available()) {
            // Print the incomming data
            Serial.print("GOT: ");
            Serial.println(ServerController::getClient().read());
        }
    }

    // Stream the strip data if we're connected
    if(ServerController::isClientConnected()) {
        // Stream the strip data
        this->strip.stream();

        // End
        // TODO: Replace this with proper packet handling
        ServerController::getClient().write('y');
        Serial.write('y');

        // Wait for the begin bytes
        // TODO: Replace this with proper handshaking!
        while(!ServerController::getClient().available() || ServerController::getClient() != 'o')
            updateLogic();
        while(!ServerController::getClient().available() || ServerController::getClient() != 'z')
            updateLogic();
    }

    // Update everything
    updateLogic();
}

void Core::updateLogic() {
    // Update the memory manager
    MemoryManager::update();

    // Update the LED manager
    LedManager::update();

    // Update the server controller status
    ServerController::update();
}

void Core::smartDelay(int delay) {
    // Create a timer, to track the passed time
    Timer timer(delay);

    // Start the timer
    timer.start();

    // Call the update method until the timer has passed the specified delay
    while(!timer.isFinished())
        updateLogic();
}