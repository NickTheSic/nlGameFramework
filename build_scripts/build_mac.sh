#!/bin/bash

INCLUDES="-Inl_lib/ -Iprojects/$1/"
FLAGS="-g -v"
COMPILER=clang
OUTPUT="-o _build/mac/$1.a"
LIBS="-lobjc -framework Foundation"

NLBUILD="projects/main/mmain.m projects/$1/$1.c nl_lib/build_nl_lib.c"

$COMPILER $INCLUDES $FLAGS $NLBUILD $LIBS $OUTPUT
