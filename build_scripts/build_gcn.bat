
set GCN_COMPILER= %DEV_KIT_PRO_ROOT%\devkitPPC\bin\powerpc-eabi-gcc-14.2.0
set GCN_INCLUDES= -I%DEV_KIT_PRO_ROOT%\libogc\include
set GCN_LIBS= -L%DEV_KIT_PRO_ROOT%\libogc\lib\cube -lm  -logc
set GCN_FLAGS= -mogc -mcpu=750 -meabi -mhard-float

set DEFINES=-DGEKKO -DGCN_GEKKO

set includes=-Inl_lib -Iprojects/%1
set flags=-Wall -Wextra -g -O2
set output=_build/gcn/

set files=nl_lib/build_nl_lib.c projects/main/main.c projects/%1/%1.c

@echo on

%GCN_COMPILER% %DEFINES% %files% %GCN_INCLUDES% %GCN_LIBS% %includes% %GCN_FLAGS% %flags% -o%output%nl_lib.elf
%DEV_KIT_PRO_ROOT%\tools\bin\elf2dol %output%nl_lib.elf %output%game.dol

@echo off