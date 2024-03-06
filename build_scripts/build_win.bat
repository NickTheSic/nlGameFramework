@echo off

pushd _build\win32

set libs=nl_lib.lib ole32.lib
set flags=/Od /EHa /Zi /std:c11 /wd5105
set includes=/I../../nl_lib

echo on

cl %flags% %includes% %1 %2 %libs%

@echo off
popd
echo on