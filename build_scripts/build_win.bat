@echo off

IF NOT EXIST "_build/win32" (mkdir "_build/win32")
IF NOT EXIST "_build/win32/%1" (mkdir "_build/win32/%1")
IF NOT EXIST "_build/win32/%1/OpenAL32.lib" (xcopy /s nl_lib/libs/OpenAL32.lib _build/win32/%1)

pushd _build\win32\%1

set libs=User32.lib OpenGl32.lib gdi32.lib OpenAL32.lib ole32.lib
set flags=/Od /EHa /Zi /std:c11 /W4
set includes=/I../../../nl_lib /I../../../projects/%1

set FILES=../../../nl_lib/build_nl_lib.c ../../../projects/%1/%1.c


@echo on

:: rc /r ../../../res/win_icon.rc /OUT ../../../res :: create a file that contains app icon
cl %flags% %EXTRA_FLAGS_WIN% %includes% %FILES% ../../../res/win_icon0.res %libs% /link /LIBPATH:"../../../nl_lib/libs"

@echo off

popd