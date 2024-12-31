#! /bin/bash

libs=""
flags="-Wall -Wextra -std=c11"
includes="-Inl_lib -Iprojects/$1"

gcc $flags $includes projects/$1/$1.c nl_lib/build_nl_lib/linux.c
