#!/bin/bash
gcc kinematic.c -o kinematic $(sdl2-config --cflags --libs) -lm
./kinematic
rm kinematic
