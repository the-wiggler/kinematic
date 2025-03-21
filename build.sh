#!/bin/bash
gcc window.c -o window $(sdl2-config --cflags --libs)
./window
rm window
