#!/usr/bin/env bash 

mkdir -p "_build/glfwtux/$1"
pushd "_build/glfwtux/$1"

libs="-lpthread -ldl -lm -L../../../nl_lib/libs -lfreetype -lglfw3"
flags="-g -O0 --static -DNL_BUILD_GLFW"
includes="-I../../../nl_lib -I../../../projects/$1 -I../../../nl_lib/third_party/freetype/include -I../../../nl_lib/third_party/glfw/include"
FILES="../../../nl_lib/build_nl_lib.c ../../../projects/$1/$1.c"

gcc $flags $includes $FILES $libs -o $1.out

compile_status=$?

popd

(exit $compile_status)