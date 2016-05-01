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

#ifndef DYNAMBI_RANDOM_H
#define DYNAMBI_RANDOM_H

#include <Arduino.h>

/**
 * Random class.
 * A class to generate random numbers.
 */
class Random {
public:
    /**
     * Get a random number, from zero to the specified maximum number. The maximum number is excluded.
     *
     * @param max Maximum number (excluded).
     *
     * @return A random number.
     */
    static int nextInt(int max);

    /**
     * Get a random number, from the specified minimum number to the specified maximum number.
     * The maximum number is excluded.
     *
     * @param min Minimum number (included).
     * @param max Maximum number (excluded).
     *
     * @return A random number.
     */
    static int nextInt(int min, int max);

    /**
     * Get a random boolean.
     *
     * @return A random boolean.
     */
    static bool nextBool();

    /**
     * Randomize the current random seed.
     */
    static void randomize();

    /**
     * Set the current random seed.
     */
    static void setSeed(unsigned int seed);

    /**
     * Get a random number, that isn't based of a seed. The main random instance isn't used to generate this number.
     * This can be used to properly seed the current random instance with a number that is as random as possible.
     *
     * The returned value is 1 or greater.
     * The limit of the returned number isn't specified, and can differ greatly over time.
     *
     * @return A random number.
     */
    static unsigned int nextIntWithoutSeed();
};

#endif //DYNAMBI_RANDOM_H
