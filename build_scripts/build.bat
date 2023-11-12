IF "%1"==""(
    echo missing first parameter
)

IF /I %1==win(
call "build_scripts/build_win32_lib.bat" && call "build_scripts/build_win_sandbox.bat" %2
)

IF /I %1==web(
call "build_web" %2
)
