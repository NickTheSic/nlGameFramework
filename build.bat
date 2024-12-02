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
call "build_scripts/build_win_aio.bat" ../../nl_lib/build_nl_lib.c ../../projects/main/main.c ../../projects/%2/%2.c
goto compile_hit
)


IF /I %1==web (
call "build_scripts/build_web" %2
@echo off
goto compile_hit
)

IF /I %1==exgcn (
    call "build_scripts/build_gcn_example" %2
    goto compile_hit
)

IF /I %1==gcn (
    call "build_scripts/build_gcn" %2
    goto compile_hit
)

IF /I %1==nds (
    call "build_scripts/build_nds" %2
    goto compile_hit
)

IF /I %1==wii (
    call "build_scripts/build_wii" %2
    goto compile_hit
)

IF /I %1==gba (
    call "build_scripts/build_gba" %2
    goto compile_hit
)

IF /I %1==psx (
    call "build_scripts/build_psx.bat" %2
    goto compile_hit
)

:exit
:compile_hit

@echo on