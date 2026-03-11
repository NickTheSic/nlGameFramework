
x86_64-w64-mingw32-gcc -I../nl_lib/third_party/freetype/include -c ../nl_lib/third_party/freetype/freetype_build.c
x86_64-w64-mingw32-ar rcs libfreetype.a freetype_build.o
