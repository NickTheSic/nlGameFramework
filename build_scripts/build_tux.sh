#!/bin/bash

libs=
flags=
includes=-Inl_lib

gcc $flags $includes projects/$1/$1.c nl_lib/build_nl_lib.c
