@echo off

pushd _build\win32

set libs=nl_lib.lib
set flags=/Od /EHa /Zi
set includes=/I../../nl_lib

echo on

cl %flags% %includes% %1 %libs%

@echo off
popd
echo on