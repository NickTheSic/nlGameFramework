#!/bin/bash
 
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
    emrun _build/web/index.html
fi

if [ "$1" == "tux" ]
then
    echo err not implemented
fi