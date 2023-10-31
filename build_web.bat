
@echo off

set DATA=--preload-file data 


set includes=-Inl_lib
set shell_file=--shell-file MinimalShell.html
set flags=-Wall -Wextra -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFULL_ES3 -sFULL_ES2

set output=_build/web/

@echo on

emcc -c nl_lib/build_nl_lib.c -o%lib_output%nl_lib.o && emcc %flags% %shell_file% %includes% %lib_output%nl_lib.o sandbox/main.c -o%output%index.html
