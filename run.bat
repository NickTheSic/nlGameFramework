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
    D:\Downloads\Dolphin-x64\Dolphin.exe _build\gcn\hello_world.dol
)

@echo on
