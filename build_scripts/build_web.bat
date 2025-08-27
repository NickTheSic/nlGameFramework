@echo off

set DATA=--preload-file data 

set includes=-Inl_lib -Iprojects/%1
set shell_file=--shell-file build_scripts/MinimalShell.html
set flags=-Wall -Wextra -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFULL_ES3 -sFULL_ES2
:: dist flags are for debug flags or O2 flags
set dist_flags= -g
set EMCC_DEBUG=0

IF NOT EXIST "_build\web\%1\" mkdir "_build\web\%1"
set output="_build/web/%1/"

@echo on

emcc %flags% %dist_flags% %EXTRA_FLAGS_WEB% %shell_file% %includes% %2 nl_lib/build_nl_lib.c projects/%1/%1.c %DATA% -o%output%index.html

@echo off