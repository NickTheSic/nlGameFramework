
set EXTRA_APIKEY_DEFINES=-DLOOT_LOCKER_GAME_KEY=%LOOTLOCKER_GAMEAPI_KEY% -DWHALEPASS_PUBLISH_KEY=%WHALEPASSGG_PUBLISHKEY% -DWHALEPASS_SERVER_KEY=%WHALEPASSGG_SERVERKEY% -DWHALEPASS_GAME_ID=%WHALEPASSGG_GAMEID%

set EXTRA_FLAGS_WEB=-sFETCH %EXTRA_APIKEY_DEFINES%
set EXTRA_FLAGS_WIN=Ws2_32.lib %EXTRA_APIKEY_DEFINES%
