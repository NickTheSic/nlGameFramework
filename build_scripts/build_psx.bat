:: Will be running this from an already setup shell on another machine.
:: There is no real setup required as that shell script does it for me.

set FLAGS=-Wall -g -O3
set OUTPUT=_build\psx
set INCLUDES=-Inl_lib
set FILES=nl_lib/build_nl_lib.c projects/main/main.c
set DEFINES=-D__PSX__

set COMPILE_LINE=%FLAGS% -Xo$80010000 %INCLUDES% %DEFINES% %FILES% projects\%1\%1.c 

IF NOT EXIST %OUTPUT%/NUL mkdir %OUTPUT%
@echo on

:: NA
ccpsx -DNTSCVIDEOMODE=1 %COMPILE_LINE% -o%OUTPUT%\psNA.cpe,%OUTPUT%\psNA.sym,%OUTPUT%\psNA.map && cpe2x /ca %OUTPUT%\psNA.cpe  

:: EU
::ccpsx -DPALVIDEOMODE=1 %COMPILE_LINE% -o%OUTPUT%\psEU.cpe,%OUTPUT%\psEU.sym,%OUTPUT%\psEU.map && cpe2x /ce %OUTPUT%\psEU.cpe

:: JP
::cpe2x /cj %OUTPUT%\psJP.cpe
@echo off
