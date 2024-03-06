@echo off
pushd _build\win32

set libs=User32.lib OpenGl32.lib gdi32.lib OpenAL32.lib
set flags=/Od /EHa /Zi /c /analyze /std:c11


echo on


cl %flags% ../../nl_lib/build_nl_lib.c && lib.exe /OUT:nl_lib.lib build_nl_lib.obj %libs%


@echo off
popd
echo on