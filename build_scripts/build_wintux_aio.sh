#!/bin/bash

libs="-L/usr/x86_64-w64-mingw32/lib/ -L/usr/lib -Lnl_lib/libs/ -luser32 -lopengl32 -lgdi32 -lole32 -lOpenAL32"
flags=
includes="-Inl_lib -I/usr/x86_64-w64-mingw32/include/"

output="_build/win/"

x86_64-w64-mingw32-gcc-win32 $flags $includes $1 $2 $3 $libs -o $output"build_nl_lib.exe"
