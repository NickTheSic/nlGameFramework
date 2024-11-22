pushd _build
@echo on

7z a -tzip web_game.zip web
butler push web_game.zip %ITCH_IO_USER%/%1:html

@echo off
popd