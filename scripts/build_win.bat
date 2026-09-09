@echo off

IF NOT EXIST "_build/win32" (mkdir "_build/win32")
IF NOT EXIST "_build/win32/%1" (mkdir "_build/win32/%1")

pushd _build\win32\%1

set libs=User32.lib OpenGl32.lib gdi32.lib ole32.lib freetype.lib

:: 5105 - in windows.h  
:: 4244 - float to int conversions
:: 4018 - signed unsigned mismatch
:: 4305 - truncation from double to float

set flags=/Od /EHa /Zi /std:c11 /W4 /WX /wd5105 /wd4244 /wd4018 /wd4305 

:: The following only apply to Lua at the moment
:: 4310 - Cast Truncates constant value 
:: 4324 - structure was padded due to alignment specifier
:: 4709 - comma operator within array index expression
:: 4701 - potentionally uninitialized local variable
:: 4702 - unreachable code
set lua_warning_supress=/wd4310 /wd4324 /wd4709 /wd4701 /wd4702

set includes=/I../../../nl_lib /I../../../projects/%1 /I../../../nl_lib/third_party/freetype/include

set FILES=../../../nl_lib/build_nl_lib.c ../../../projects/%1/%1.c


@echo on

:: /Fe ::Apparently this controls the name of the executable
:: rc /r ../../../res/win_icon.rc /OUT ../../../res :: create a file that contains app icon
cl %flags% %lua_warning_supress% %EXTRA_FLAGS_WIN% %includes% %FILES% ../../../res/win_icon0.res %libs% /link /LIBPATH:"../../../nl_lib/libs"

@echo off

popd