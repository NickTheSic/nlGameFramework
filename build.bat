@echo off

IF "%1"=="" (
    echo missing first parameter, should be the platform
    goto exit
)

IF "%2"=="" (
    echo missing second parameter. should be the project to build. If you specified the project you may be missing the platform
    goto exit
)

IF NOT EXIST _build/NUL mkdir _build

IF /I %1==win (
    call "build_scripts/build_win.bat" %2
    goto compile_hit
)

IF /I %1==web (
    call "build_scripts/build_web" %2 
    @echo off
    goto compile_hit
)

:compile_hit
:exit

@echo on