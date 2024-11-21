@echo off

set COMP=%DEV_KIT_PRO_ROOT%\devkitARM\bin\arm-none-eabi-gcc
set ARCH=-mthumb -mthumb-interwork
set FLAG=-g -Wall -O2 -mcpu=arm7tdmi -mtune=arm7tdmi
set INCL=-I%DEV_KIT_PRO_ROOT%\libtonc\include -I%DEV_KIT_PRO_ROOT%\libgba\include -Inl_lib
set LIBS=-L%DEV_KIT_PRO_ROOT%\libtonc\lib -L%DEV_KIT_PRO_ROOT%\libgba\lib -lmm -ltonc
set SPEC=-specs=gba.specs
set specroot=%DEV_KIT_PRO_ROOT%\devkitARM\lib\

@echo on

%COMP% %FLAG% %ARCH% %INCL% -c build_nl_lib.c -o nl_lib.o
%COMP% %FLAG% %ARCH% %INCL% -c projects/%1/%1.c -o %1.o
%COMP% -g %ARCH% -Wl,-Map,_build\gba\%1.map %SPEC% nl_lib.o %1.o %LIBS% -o %1.elf
%DEV_KIT_PRO_ROOT%\devkitARM\bin\arm-none-eabi-objcopy -O binary %1.elf %1.gba
%DEV_KIT_PRO_ROOT%\tools\bin\gbafix.exe %1.gba -thello -c0000 -m00
