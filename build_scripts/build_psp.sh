#!/bin/bash

PSP_SDK=$(psp-config -p)
PSP_DEV=$(psp-config -d)
INCLUDES="-I$PSP_SDK/include -I$PSP_DEV/psp/include -Inl_lib -Iprojects/$1"
LIBDIR="-L$PSP_SDK/lib -L$PSP_DEV/lib -L$PSP_DEV/psp/lib"
# LIBS="-lpspdebug -lpspdisplay -lpspge -lpspgu -lpspctrl -lpsphprm -lpspvramalloc -lpspvfpu -lSDL2 -lGL -lGLU -lglut -lSDL2_mixer -lvorbisfile -lvorbis -logg -lmodplug -lpthread -lpthreadglue -lstdc++ -lpspaudio -lpspaudiolib"
LIBS="-lpspdebug -lpspdisplay -lpspge -lpspgu -lpspctrl -lpspvramalloc -lpspvfpu -lpthread -lpthreadglue -lstdc++ -lpspaudio -lpspaudiolib"
DEFINES="-DPSP -D_PSP_FW_VERSION=600 -D__PSP__ $2" 
FLAGS="-Wall -Wextra -g -Wl,-zmax-page-size=128 -Wl,-Map,_build/psp/$1.map"
PRX_SPECS="-specs=$PSP_SDK/lib/prxspecs -Wl,-q,-T$PSP_SDK/lib/linkfile.prx"
OUTPUT="_build/psp"

mkdir -p $OUTPUT

ICON0=res/icon0.png    #png Recommended: 144x80 
ICON1=NULL              #pmf
PIC0=NULL               #png
PIC1=res/pic1.png      #png Recommended: 480x272
SND0=res/snd0.at3    #sound.at3 
PSAR=NULL               #data.psar

if [ ! -d "_build/psp/$1" ]
then
mkdir "_build/psp/$1"
fi

psp-gcc $DEFINES $INCLUDES $FLAGS $LIBDIR -o $OUTPUT/$1.elf nl_lib/build_nl_lib.c projects/$1/$1.c $LIBS && echo "code compiled" 
psp-fixup-imports $OUTPUT/$1.elf && echo "fixed imports" 
mksfoex -d MEMSIZE=1 -s APP_VER=01.00 $1 $OUTPUT/PARAM.SFO && pack-pbp $OUTPUT/$1/EBOOT.PBP $OUTPUT/PARAM.SFO $ICON0 $ICON1 $PIC0 $PIC1 $SND0 $OUTPUT/$1.elf $PSAR
