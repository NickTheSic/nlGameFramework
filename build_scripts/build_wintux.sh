#!/usr/bin/env bash 

mkdir -p "_build/win32/$1"
pushd "_build/win32/$1"


libs=User32.lib OpenGl32.lib gdi32.lib ole32.lib

flags=/Od /EHa /Zi /std:c11 /W4 /WX /wd5105 /wd4244 /wd4018 /wd4305

includes=/I../../../nl_lib /I../../../projects/$1

FILES=../../../nl_lib/build_nl_lib.c ../../../projects/$1/$1.c

x86_64-w64-mingw32-gcc $flags $EXTRA_FLAGS_WIN $includes $FILES $libs 

popd