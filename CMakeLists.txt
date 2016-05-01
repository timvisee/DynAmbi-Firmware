##############################################################################
# Copyright (c) ArduinoDynambi 2016. All rights reserved.                    #
#                                                                            #
# @author Tim Visee                                                          #
# @website http://timvisee.com/                                              #
#                                                                            #
# Open Source != No Copyright                                                #
#                                                                            #
# Permission is hereby granted, free of charge, to any person obtaining a    #
# copy of this software and associated documentation files (the "Software"), #
# to deal in the Software without restriction, including without limitation  #
# the rights to use, copy, modify, merge, publish, distribute, sublicense,   #
# and/or sell copies of the Software, and to permit persons to whom the      #
# Software is furnished to do so, subject to the following conditions:       #
#                                                                            #
# The above copyright notice and this permission notice shall be included    #
# in all copies or substantial portions of the Software.                     #
#                                                                            #
# You should have received a copy of The MIT License (MIT) along with this   #
# program. If not, see <http://opensource.org/licenses/MIT/>.                #
##############################################################################

cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME ArduinoDynAmbi)
project(${PROJECT_NAME})

# The target Arduino board type
set(${CMAKE_PROJECT_NAME}_BOARD uno)
# The target port the Arduino is connected to, for uploading
set(${CMAKE_PROJECT_NAME}_PORT COM11)

set(${CMAKE_PROJECT_NAME}_SKETCH ArduinoDynAmbi.ino)
generate_arduino_firmware(${CMAKE_PROJECT_NAME})
