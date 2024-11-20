#!/bin/bash

libs="-lUser32 -lopenGL -lgdi32 -lole32 -L/usr/x86_64-w64-mingw32/lib/"
flags=
includes="-I../../nl_lib -I/usr/x86_64-w64-mingw32/include/"

output="_build/win/"

gcc $flags $includes $1 $2 $3 $libs -o $output"build_nl_lib.exe"
