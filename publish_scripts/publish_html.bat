pushd _build/web
@echo on

7z a -tzip %1.zip %1
butler push %1.zip %ITCH_IO_USER%/%1:html

@echo off
popd