#!/usr/bin/env bash

output="_build/sdltux/$1"
mkdir -p $output

flags="-Wall -Wextra -g -lm"
includes="-Inl_lib -Iprojects/$1"

gcc $flags $includes nl_lib/build_nl_lib.c projects/$1/$1.c -o$output/$1