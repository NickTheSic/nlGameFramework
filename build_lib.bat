pushd _build

set libs=User32.lib OpenGl32.lib gdi32.lib
set flags=/Od /EHa /Zi /c

cl %flags% ../nl_lib/build.c 
lib.exe /OUT:nl_lib.lib build.obj %libs%

popd