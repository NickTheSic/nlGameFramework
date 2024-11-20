@echo off

set OUTDIR=_build\nds\

set COMPILER=%DEV_KIT_PRO_ROOT%\devkitARM\bin\arm-none-eabi-g++
set ARCH=-march=armv5te -mtune=arm946e-s -mthumb 
set DEFINES= -D__NDS__ -DARM9 
set FLAGS=-g -Wall -O2 -ffunction-sections -fdata-sections %arch%

set INCLUDES= -I%DEV_KIT_PRO_ROOT%\libnds\include -I%DEV_KIT_PRO_ROOT%\calico\include
set LIBS=-L%DEV_KIT_PRO_ROOT%\libnds\lib -L%DEV_KIT_PRO_ROOT%\calico\lib -ldswifi9 -lfat -lmm9 -lnds9 -lcalico_ds9 

set CODE=%DEV_KIT_PRO_ROOT%\examples\nds\Graphics\Printing\print_both_screens\source\template.c

set icon=%DEV_KIT_PRO_ROOT%\calico\share\nds-icon.bmp
set arm7elf=-7 %DEV_KIT_PRO_ROOT%\calico\bin\ds7_maine.elf

@echo on

%COMPILER% %DEFINES% %FLAGS% %INCLUDES% -c %CODE% -o %OUTDIR%nl_lib.o
%COMPILER% %ARCH% -specs=%DEV_KIT_PRO_ROOT%\calico\share\ds9.specs -g  %OUTDIR%nl_lib.o %LIBS% -o %OUTDIR%nl_lib.elf
%DEV_KIT_PRO_ROOT%\tools\bin\ndstool -c  %OUTDIR%game.nds -9  %OUTDIR%nl_lib.elf %arm7elf% -b %icon% "Test;A Test;Working?" 

@echo off