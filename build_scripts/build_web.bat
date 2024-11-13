
@echo off

set DATA=--preload-file data 


set includes=-Inl_lib
set shell_file=--shell-file build_scripts/MinimalShell.html
set flags=-Wall -Wextra -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFULL_ES3 -sFULL_ES2

set output=_build/web/

@echo on

emcc %flags% %shell_file% %includes% nl_lib/build_nl_lib.c projects/sandbox/main.c projects/%1/%1.c %data% -o%output%index.html

@echo off