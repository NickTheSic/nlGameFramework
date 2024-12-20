#!/bin/bash

OUTPUT_DIR=_build/mac/$1.app

mkdir -p $OUTPUT_DIR/Contents/Resources
mkdir $OUTPUT_DIR/Contents/MacOS

INCLUDES="-Inl_lib/ -Iprojects/$1/"
FLAGS="-g"
COMPILER=clang
OUTPUT="-o $OUTPUT_DIR/Contents/MacOS/build_nl_lib"
LIBS="-lobjc -framework Foundation"
ARCH="-arch x86_64"

NLBUILD="projects/main/mmain.m projects/$1/$1.c nl_lib/build_nl_lib.c"

$COMPILER $INCLUDES $ARCH $FLAGS $NLBUILD $LIBS $OUTPUT

    cp res/icon1.icns $OUTPUT_DIR/Contents/Resources/icon.icns
    cp res/info.plist $OUTPUT_DIR/Contents/info.plist
