@echo off

IF "%1"=="" (
    echo missing first parameter, should be the platform
)

IF "%2"=="" (
    echo missing second parameter. should be the project to build. If you specified the project you may be missing the platform
)

IF /I %1==win (
call "build_scripts/build_win_aio.bat" ../../nl_lib/build_nl_lib.c ../../projects/sandbox/main.c ../../projects/%2/%2.c
goto compile_hit
)

IF /I %1==web (
call "build_scripts/build_web" %2
@echo off
goto compile_hit
)

:compile_hit

@echo on