#! /bin/bash

libs="-lm -lopenal"
flags="-Wall -Wextra -std=c11"
includes="-Inl_lib -Iprojects/$1"
output="_build/tux/program"

mkdir -p $output

gcc $flags $includes projects/$1/$1.c nl_lib/build_nl_lib/linux.c $libs
