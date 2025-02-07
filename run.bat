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

IF %1==gcn (
    %DOLPHIN_EMULATOR% _build\gcn\game.dol
    goto end
)

IF %1==wii (
    %DOLPHIN_EMULATOR% _build\wii\game.dol
    goto end
)

IF %1==psp (
    IF "%2"=="" (
        echo need to specify game to run
        goto end
    )
    call "%PPSSPP_EMULATOR%" -v _build\psp\%2\EBOOT.PBP
    goto end
)

IF %1==nds (
    %DESMUME_EMULATOR% "_build\nds\game.nds"
    goto end
)

IF %1==gba (
    echo gba run not set up
    goto end
)

:end

@echo on
