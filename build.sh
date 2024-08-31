#! /bin/bash

if [ $# -eq 0 ]
then
    echo please specify the platform
fi

if [ "$1" == "win" ]
then
    echo err not setup
fi

if [ "$1" == "web" ]
then 
    ./build_scripts/build_web.sh $2
fi

if [ "$1" == "tux" ]
then
    ./build_scripts/build_tux.sh $2
fi