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

#include "Random.h"

int Random::nextInt(int max) {
    return nextInt(0, max);
}

int Random::nextInt(int min, int max) {
    return (int) random((long) min, (long) max);
}

bool Random::nextBool() {
    return nextInt(0, 2) == 0;
}

void Random::randomize() {
    setSeed(Random::nextIntWithoutSeed());
}

void Random::setSeed(unsigned int seed) {
    // Set the seed in the Arduino library
    randomSeed(seed);
}

unsigned int Random::nextIntWithoutSeed() {
    // Determine a base number, based on the number of milliseconds the Arduino has run
    unsigned int num = (unsigned int) (millis() % 9999);

    // Semi-randomize the defined number using analog reads
    for(int i = 0; i < 6; i++)
        num *= analogRead((uint8_t) i);

    // Return the random value
    return num;
}