
set DKP=D:\DevkitPro\

set WII_COMPILER= %DKP%devkitPPC\bin\powerpc-eabi-gcc-14.2.0
set WII_INCLUDES= -I%DKP%libogc\include
set WII_LIBS= -L%DKP%libogc\lib\wii -lm -logc -lwiiuse -lbte
set WII_FLAGS= -mrvl -mcpu=750 -meabi -mhard-float

set DEFINES=-DGEKKO -DWII_GECKO

set includes=-Inl_lib
set flags=-Wall -Wextra -g -O2
set output=_build/wii/

set files=nl_lib/build_nl_lib.c projects/sandbox/main.c projects/%1/%1.c

@echo on

%WII_COMPILER% %DEFINES% %files% %WII_INCLUDES% %WII_LIBS% %includes% %WII_FLAGS% %flags% -o%output%nl_lib.elf
%DKP%tools\bin\elf2dol %output%nl_lib.elf %output%%1.dol

@echo off