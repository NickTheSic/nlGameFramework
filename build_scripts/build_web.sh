
DATA="--preload-file data"
includes="-Inl_lib -Iprojects/$1"
shell_file="--shell-file build_scripts/MinimalShell.html"
flags="-Wall -Wextra -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFULL_ES3 -sFULL_ES2"

dist_flags="-g"
EMCC_DEBUG=0
 
output="_build/web/$1"
mkdir -p $output

emcc $flags $dist_flags $EXTRA_FLAGS_WEB $shell_file $includes $2 nl_lib/build_nl_lib.c projects/$1/$1.c $data -o$output/index.html

