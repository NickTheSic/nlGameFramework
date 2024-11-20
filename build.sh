#!/bin/bash

if [ $# -eq 0 ]
then
    echo please specify the platform
fi

if [ "$1" == "win" ]
then
    ./build_scripts/build_wintux_aio.sh nl_lib/build_nl_lib.c projects/sandbox/main.c projects/$2/$2.c
fi

if [ "$1" == "web" ]
then 
    ./build_scripts/build_web.sh $2
fi

if [ "$1" == "tux" ]
then
    ./build_scripts/build_tux.sh $2
fi