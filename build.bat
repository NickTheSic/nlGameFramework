@echo off

IF "%1"=="" (
    echo missing first parameter
)

IF "%2"=="" (
    echo missing second parameter
)

IF /I %1==win_x (
call "build_scripts/build_win32_lib.bat" && call "build_scripts/build_win_sandbox.bat" %2
)

IF /I %1==win (
call "build_scripts/build_win_aio.bat" ../../nl_lib/build_nl_lib.c ../../projects/sandbox/main.c ../../projects/%2/%2.c
)

@echo off

IF /I %1==web (
call "build_scripts/build_web" %2
)

@echo on