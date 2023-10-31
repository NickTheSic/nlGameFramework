pushd _build

set libs=nl_lib.lib
set flags=/Od /EHa /Zi
set includes=/I../nl_lib

cl %flags% %includes% %1 %libs%

popd