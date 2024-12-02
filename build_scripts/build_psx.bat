:: Will be running this from an already setup shell on another machine.
:: There is no real setup required as that shell script does it for me.

set FLAGS=-Wall -g -O3
set OUTPUT=_build\psx
set INCLUDES=-Inl_lib
set FILES=nl_lib/build_nl_lib.c projects/main/main.c
set DEFINES=-D__PSX__

IF NOT EXIST %OUTPUT%/NUL mkdir %OUTPUT%
@echo on

ccpsx %FLAGS% -Xo$80010000 %DEFINES% -DNTSCVIDEOMODE=1 %FILES% projects\%1\%1.c -o%OUTPUT%\psNA.cpe,%OUTPUT%\psNA.sym,%OUTPUT%\psNA.map

:: NA
cpe2x /ca %OUTPUT%\psNA.cpe  


::ccpsx %FLAGS% -Xo$80010000 %DEFINES% -DPALVIDEOMODE=1 %FILES% projects\%1\%1.c -o%OUTPUT%\psEU.cpe,%OUTPUT%\psEU.sym,%OUTPUT%\psEU.map
:: EU
::cpe2x /ce %OUTPUT%\psEU.cpe

:: JP
::cpe2x /cj %OUTPUT%\psJP.cpe
@echo off
