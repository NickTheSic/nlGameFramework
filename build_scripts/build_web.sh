#!/bin/sh

if [ $# -eq 0 ]
then
    echo please specify the project for web
fi

data="--preload-file data"

includes="-Inl_lib"
shell_file="--shell-file build_scripts/MinimalShell.html"
flags="-Wall -Wextra -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFULL_ES3 -sFULL_ES2"

output="_build/web/"

emcc $flags $shell_file $includes nl_lib/build_nl_lib.c projects/sandbox/main.c projects/$1/$1.c $data -o ${output}"index.html"