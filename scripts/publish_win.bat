pushd _build
@echo on

7z a -tzip win_game.zip win32
butler push win_game.zip %ITCH_IO_USER%/%1:win64

@echo off
popd