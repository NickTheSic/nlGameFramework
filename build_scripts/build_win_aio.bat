@echo off

IF NOT EXIST "_build/win32" (mkdir "_build/win32")

pushd _build\win32

set libs=User32.lib OpenGl32.lib gdi32.lib OpenAL32.lib ole32.lib
set flags=/Od /EHa /Zi /std:c11 /W4
set includes=/I../../nl_lib

echo on

:: rc /r ../../res/win_icon.rc /OUT ../../res :: create a file that contains app icon
cl %flags% %includes% %1 %2 %3 ../../res/win_icon0.res %libs%

@echo off
popd