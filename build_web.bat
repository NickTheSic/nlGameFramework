
@echo off

set DATA=--preload-file data 


set includes=-Inl_lib
set shell_file=--shell-file MinimalShell.html
set flags=-Wall -Wextra -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFULL_ES3 -sFULL_ES2

set output=_build/web/

@echo on

emcc %flags% %shell_file% %includes% nl_lib/build_nl_lib.c sandbox/main.c %1/%1.c -o%output%index.html