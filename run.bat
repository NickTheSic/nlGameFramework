@echo off
IF "%1"=="" (
    echo missing first parameter
    goto end
)

IF %1==win (
    call "_build//win32//build_nl_lib.exe"
    goto end
)

IF %1==web (
    emrun _build\web\index.html
    goto end
)

:end

@echo on
