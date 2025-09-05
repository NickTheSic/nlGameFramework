#!/usr/bin/env bash

if [ $# -eq 0 ]
then
    echo please specify the platform and game
fi

if [ "$1" == "html" ]
then 
    ./publish_scripts/publish_html.sh $2
fi