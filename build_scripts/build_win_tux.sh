#!/bin/bash

libs="-lUser32 -lOpenGl32 -lgdi32 -lOpenAL32 -lole32"
flags="-Wall -Wextra -g -O2"
includes="-Inl_lib -Iprojects/$1"

FILES="nl_lib/build_nl_lib.c projects/$1/$1.c"

:: rc /r ../../res/win_icon.rc /OUT ../../res :: create a file that contains app icon
x86_64-w64-mingw32-gcc $flags $EXTRA_FLAGS_WIN $includes $FILES ../../res/win_icon0.res $libs
