:: A more manual build all for now

set PLATFORM=%1

call "build.bat" %PLATFORM% _ProjectTemplate
call "build.bat" %PLATFORM% 1hello_world
call "build.bat" %PLATFORM% 2basic_audio
call "build.bat" %PLATFORM% basic_level_editor
call "build.bat" %PLATFORM% batch_render
call "build.bat" %PLATFORM% batch2d
call "build.bat" %PLATFORM% graphics
call "build.bat" %PLATFORM% IDGJ5_Fish
call "build.bat" %PLATFORM% metroidvania
call "build.bat" %PLATFORM% metroidvaniaMJ172_Security
call "build.bat" %PLATFORM% new_ui
call "build.bat" %PLATFORM% non_batch_graphics
call "build.bat" %PLATFORM% pd_style_game
call "build.bat" %PLATFORM% socket_request
call "build.bat" %PLATFORM% ui_batch
call "build.bat" %PLATFORM% ui_stuff
