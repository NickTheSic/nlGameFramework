
cl /I../nl_lib/third_party/freetype/include /c ../nl_lib/third_party/freetype/freetype_build.c
lib /out:freetype.lib freetype_build.obj
