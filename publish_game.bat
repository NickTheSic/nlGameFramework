@echo off
IF "%1"=="" (
    echo missing first parameter, should be the platform
)

IF "%2"=="" (
    echo missing second parameter. should be the project
)


:: You will have needed to run butler at least once on the target machine to initialize your account to be able to just use this to push
:: This also assumes that you are pushing the build to itch.io.  This is what I do while participating in game jams so I don't have to leave my editor 


IF /I %1==win (
call "publish_scripts/publish_win" %2
goto publish_success
)

IF /I %1==html (
call "publish_scripts/publish_html" %2
goto publish_success
)

echo incomplete publish platform

:publish_success
