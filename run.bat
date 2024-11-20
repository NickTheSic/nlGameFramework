@echo off
IF "%1"=="" (
    echo missing first parameter
)

IF %1==win (
    call "_build//win32//build_nl_lib.exe"
)

IF %1==web (
    emrun _build\web\index.html
)

IF %1==gcn (
    %DOLPHIN_EMULATOR% _build\gcn\game.dol
)

IF %1==psp (
    %PPSSPP_EMULATOR% _build\psp\%2\EBOOT.PBP
)

@echo on
