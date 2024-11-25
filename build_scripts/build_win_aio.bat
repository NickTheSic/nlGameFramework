@echo off

pushd _build\win32

set libs=User32.lib OpenGl32.lib gdi32.lib OpenAL32.lib ole32.lib
set flags=/Od /EHa /Zi /std:c11 /wd5105
set includes=/I../../nl_lib

echo on

:: rc /r ../../program.rc /OUT _build\win32 :: create a file that contains app icon
cl %flags% %includes% %1 %2 %3 program.res %libs%

@echo off
popd