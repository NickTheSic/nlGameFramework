#!/bin/bash

if [ $1 == "mac" ]
then
    ./_build/mac/$2.app/Contents/MacOS/build_nl_lib
fi
