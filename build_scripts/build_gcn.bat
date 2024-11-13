
set DKP=D:\DevkitPro\

set GCN_COMPILER= %DKP%devkitPPC\bin\powerpc-eabi-gcc-14.2.0
set GCN_INCLUDES= -I%DKP%libogc\include
set GCN_LIBS= -L%DKP%libogc\lib\cube -lm  -logc
set GCN_FLAGS= -mogc -mcpu=750 -meabi -mhard-float

set DEFINES=-DGEKKO

set includes=-Inl_lib
set flags=-Wall -Wextra -g -O2
set output=_build/gcn/

set files=nl_lib/build_nl_lib.c projects/sandbox/main.c projects/%1/%1.c

@echo on

%GCN_COMPILER% %DEFINES% %files% %GCN_INCLUDES% %GCN_LIBS% %includes% %GCN_FLAGS% %flags% -o%output%nl_lib.elf
%DKP%tools\bin\elf2dol %output%nl_lib.elf %output%%1.dol

@echo off