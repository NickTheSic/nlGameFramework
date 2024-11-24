@echo off

set COMPILER=%DEV_KIT_PRO_ROOT%\devkitA64\bin\aarch64-none-elf-g++
set FLAGS=-g -Wall -O2 -ffunction-sections
set ARCH=-march=armv8-a+crc+crypto -mtune-cortex-a57 -mtp=soft -fPIE
set INCLUDE=-I%DEV_KIT_PRO_ROOT%\libnx\include -I%DEV_KIT_PRO_ROOT%\portlibs/switch/include
set DEFINES=-D__SWITCH__
set CXX_FLAGS=-fno-rtti -fno-exceptions 

set files=

%COMPILER% %FLAGS% %ARCH% %INCLUDE% %DEFINES% %CXX_FLAGS% -c   %files%   -o file.o
