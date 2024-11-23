@echo off

set COMP=%DEV_KIT_PRO_ROOT%\devkitARM\bin\arm-none-eabi-gcc
set ARCH=-mthumb -mthumb-interwork
set FLAG=-g -Wall -O2 -mcpu=arm7tdmi -mtune=arm7tdmi
set INCL=-I%DEV_KIT_PRO_ROOT%\libtonc\include -I%DEV_KIT_PRO_ROOT%\libgba\include -Inl_lib
set LIBS=-L%DEV_KIT_PRO_ROOT%\libtonc\lib -L%DEV_KIT_PRO_ROOT%\libgba\lib -lmm -ltonc
set SPEC=-specs=gba.specs
set DEFS=-D__GBA__
set OUTPUT=_build\gba

@echo on

%COMP% %FLAG% %ARCH% %DEFS% %INCL% -c nl_lib\build_nl_lib.c -o %OUTPUT%\nl_lib.o
%COMP% %FLAG% %ARCH% %DEFS% %INCL% -c projects/%1/%1.c -o %OUTPUT%\%1.o
%COMP% %FLAG% %ARCH% %DEFS% %INCL% -c projects/main/main.c -o %OUTPUT%\main.o
%COMP% -g %ARCH% -Wl,-Map,%OUTPUT%\%1.map %SPEC% %OUTPUT%\nl_lib.o %OUTPUT%\%1.o %OUTPUT%\main.o %LIBS% -o %OUTPUT%\%1.elf
%DEV_KIT_PRO_ROOT%\devkitARM\bin\arm-none-eabi-objcopy -O binary %OUTPUT%\%1.elf %OUTPUT%\%1.gba
%DEV_KIT_PRO_ROOT%\tools\bin\gbafix.exe %OUTPUT%\%1.gba -thello -c0000 -m00
