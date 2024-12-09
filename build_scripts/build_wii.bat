
set WII_COMPILER= %DEV_KIT_PRO_ROOT%\devkitPPC\bin\powerpc-eabi-gcc-14.2.0
set WII_INCLUDES= -I%DEV_KIT_PRO_ROOT%\libogc\include
set WII_LIBS= -L%DEV_KIT_PRO_ROOT%\libogc\lib\wii -lwiiuse -lbte -logc -lm
set WII_FLAGS= -mrvl -mcpu=750 -meabi -mhard-float

set DEFINES=-DGEKKO -DWII_GEKKO

set includes=-Inl_lib -Iprojects/%1
set flags=-Wall -Wextra -g -O2
set output=_build/wii/

set files=nl_lib/build_nl_lib.c projects/main/main.c projects/%1/%1.c

@echo on

%WII_COMPILER% %DEFINES% %files% %WII_INCLUDES% %WII_LIBS% %includes% %WII_FLAGS% %flags% -o%output%nl_lib.elf
%DEV_KIT_PRO_ROOT%\tools\bin\elf2dol %output%nl_lib.elf %output%game.dol

@echo off