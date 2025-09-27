#!/usr/bin/env bash 

mkdir -p "_build/win32/$1"
pushd "_build/win32/$1"


libs="-luser32 -lopengl32 -lgdi32 -lole32 -lxaudio2_9"

flags="-Wall -Wextra -g --static"

includes="-I../../../nl_lib -I../../../projects/$1 -I/usr/x86_64-w64-mingw32/include"

FILES="../../../nl_lib/build_nl_lib.c ../../../projects/$1/$1.c"

x86_64-w64-mingw32-gcc $EXTRA_FLAGS_WIN $flags $includes $FILES $libs

popd