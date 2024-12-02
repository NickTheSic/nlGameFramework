:: Will be running this from an already setup shell on another machine.
:: There is no real setup required as that shell script does it for me.

set FLAGS=-Wall -g -O3
set OUTPUT=\_build\psx

IF NOT EXIST %OUTPUT%/NUL mkdir %OUTPUT%
@echo on

ccpsx %FLAGS% -Xo$80010000 -DNTSCVIDEOMODE=1 projects\%1\%1.c -o%OUTPUT%\psNA.cpe,%OUTPUT%\psNA.sym,%OUTPUT%\psNA.map

:: NA
cpe2x /ca %OUTPUT%\psNA.cpe  


ccpsx %FLAGS% -Xo$80010000 -DPALVIDEOMODE=1 projects\%1\%1.c -o%OUTPUT%\psEU.cpe,%OUTPUT%\psEU.sym,%OUTPUT%\psEU.map
:: EU
cpe2x /ce %OUTPUT%\psEU.cpe

:: JP
::cpe2x /cj %OUTPUT%\psJP.cpe
@echo off
