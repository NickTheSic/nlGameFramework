@echo off
set 3dmodel=FALSE
set batchrenderer=FALSE
set openal = FALSE
set renderersetup = FALSE

call "build.bat" win 3d_model && 3dmodel = TRUE
call "build.bat" win batch_render && call "build.bat" web batch_render && batchrenderer = TRUE
call "build.bat" win open_al && call "build.bat" web open_al && openal = TRUE
call "build.bat" web renderer_setup && call "build.bat" win renderer_setup && renderersetup = TRUE

@echo on

IF renderersetup==FALSE(
    echo "renderersetup failed"
)

IF 3dmodel==FALSE(
    echo "3dmodel failed"
)

IF batchrenderer==FALSE(
    echo "batchrenderer failed"
)

IF openal==FALSE(
    echo "openal failed"
)
