
:: This is to compile on the secondary laptop.
:: Based on https://n64squid.com/homebrew/n64-sdk/ dev setup 

set ROOT=c:\ultra
set gccdir=c:\ultra\gcc
set n64align=on
set GCC_CELF=on
set gccsw=-mips3 -mfp32 -funsigned-char -D_LANUAGE_C -D_ULTRA64 -D__EXTENSIONS__
::make

set DEFINES=-DNU_DEBUG -DF3DEX_GBI_2 -_MIPS_SZLONG=32 -D_MIPS_SZINT=32
set INCLUDES=-I. -Ic:\nintendo\n64kit\nusys\include -Ic:\ultra\usr\include\PR
set LIBS=-Lc:\nintendo\n64kit\nusys\lib -Lc:\ultra\usr\lib -Lc:\u;tra\gcc\mipse\lib -lnusys_d -lgultra_d -lkmc
