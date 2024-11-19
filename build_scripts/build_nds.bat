@echo off

set DKP=D:\DevkitPro
set OUTDIR=_build\nds\

set COMPILER=%DKP%\devkitARM\bin\arm-none-eabi-g++
set ARCH=-march=armv5te -mtune=arm946e-s -mthumb 
set DEFINES= -D__NDS__ -DARM9 
set FLAGS=-g -Wall -O2 -ffunction-sections -fdata-sections %arch%

set INCLUDES= -I%DKP%\libnds\include -I%DKP%\calico\include
set LIBS=-L%DKP%\libnds\lib -L%DKP%\calico\lib -ldswifi9 -lfat -lmm9 -lnds9 -lcalico_ds9 

set CODE=%DKP%\examples\nds\Graphics\Printing\print_both_screens\source\template.c

set icon=%DKP%\calico\share\nds-icon.bmp
set arm7elf=-7 %DKP%\calico\bin\ds7_maine.elf

@echo on

%COMPILER% %DEFINES% %FLAGS% %INCLUDES% -c %CODE% -o %OUTDIR%nl_lib.o
%COMPILER% %ARCH% -specs=%DKP%\calico\share\ds9.specs -g  %OUTDIR%nl_lib.o %LIBS% -o %OUTDIR%nl_lib.elf
%DKP%\tools\bin\ndstool -c  %OUTDIR%game.nds -9  %OUTDIR%nl_lib.elf %arm7elf% -b %icon% "Test;A Test;Working?" 

@echo off