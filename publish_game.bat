@echo off
IF "%1"=="" (
    echo missing first parameter, should be the platform
)

IF "%2"=="" (
    echo missing second parameter. should be the project
)

IF /I %1==win (
echo incomplete publish platform
goto publish_success
)

IF /I %1==html (
call "publish_scripts/publish_html" %2
goto publish_success
)

echo incomplete publish platform

:publish_success
