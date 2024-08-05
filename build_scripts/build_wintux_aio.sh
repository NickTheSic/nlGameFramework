#!/bin/bash

cd _build/win

libs="-lUser32 -lopenGL -lgdi32 -lole32 -L/usr/i686-w64-mingw32/lib/"
flags=
includes="-I../../nl_lib -I/usr/i686-w64-mingw32/include/"

mingw-w64