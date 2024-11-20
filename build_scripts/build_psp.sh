#!/bin/bash

PSP_SDK=$(psp-config -p)
PSP_DEV=$(psp-config -d)
INCLUDES="-I$PSP_SDK/include -I$PSP_DEV/psp/include"
LIBDIR="-L$PSP_SDK/lib -L$PSP_DEV/lib -L$PSP_DEV/psp/lib"
LIBS="-lpspdebug -lpspdisplay -lpspge"
DEFINES="-DPSP -D_PSP_FW_VERSION=600 -D__PSP__"
FLAGS="-Wl,-zmax-page-size=128"
OUTPUT="_build/psp"

if [ ! -d "_build/psp/$1" ]
then
mkdir "_build/psp/$1"
fi

psp-gcc $DEFINES $INCLUDES $FLAGS -o $OUTPUT/$1.c.obj -c projects/$1/$1.c
echo "code compiled"
psp-gcc $INCLDUES -DPSP $LIBDIR $FLAGS $OUTPUT/$1.c.obj -o $OUTPUT/$1.elf $LIBS
echo "code linked"
psp-fixup-imports $OUTPUT/$1.elf
echo "fixed imports"
mksfoex -d MEMSIZE=1 -s APP_VER=01.00 $1 $OUTPUT/PARAM.SFO
pack-pbp $OUTPUT/$1/EBOOT.PBP $OUTPUT/PARAM.SFO NULL NULL NULL NULL NULL $OUTPUT/$1.elf NULL