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


:: TODO: Don't run in emulator, setup the calls to debug on system
IF %1==psp (
    IF "%2"=="" (
        echo need to specify game to run
        goto end
    )
    call "%PPSSPP_EMULATOR%" -v _build\psp\%2\EBOOT.PBP
    goto end
)

:end
@echo on
