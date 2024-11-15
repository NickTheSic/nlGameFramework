@echo off

IF "%1"=="" (
    echo missing first parameter, should be the platform
)

IF "%2"=="" (
    echo missing second parameter. should be the project to build. If you specified the project you may be missing the platform
)

IF /I %1==win_x (
call "build_scripts/build_win32_lib.bat" && call "build_scripts/build_win_sandbox.bat" %2
)

IF /I %1==win (
call "build_scripts/build_win_aio.bat" ../../nl_lib/build_nl_lib.c ../../projects/sandbox/main.c ../../projects/%2/%2.c
)

IF /I %1==web (
call "build_scripts/build_web" %2
)

IF /I %1==exgcn (
    call "build_scripts/build_gcn_example" %2
)

IF /I %1==gcn (
    call "build_scripts/build_gcn" %2
)

IF /I %1==nds (
    call "build_scripts/build_nds" %2
)

IF /I %1==wii (
    call "build_scripts/build_wii" %2
)

@echo on