#!/bin/bash

if [ $# -eq 0 ]
then
    echo please specify the platform
fi

if [ "$1" == "tux" ]
then
    ./build_scripts/build_tux.sh $2
fi

if [ "$1" == "pspprx" ]
then 
    ./build_scripts/build_psp_prx.sh $2 $3
fi

if [ "$1" == "psp" ]
then 
    ./build_scripts/build_psp.sh $2 $3
fi

if [ "$1" == "mac" ]
then
    ./build_scripts/build_mac.sh $2
fi
