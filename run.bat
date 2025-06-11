@echo off
IF "%1"=="" (
    echo missing first parameter
    goto end
)

IF %1==win (
    call "_build//win32//%2//build_nl_lib.exe"
    goto end
)

IF %1==web (
    IF "%2"=="" (
        echo need to specify game to run
        goto end
    )
    emrun _build\web\%2\index.html
    goto end
)

:end
@echo on
