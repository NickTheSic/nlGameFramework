#include "nl_lib.h"

// Using VS2022 seems like the right play here with C so I can use intellisense
#include <windows.h> // required without WIN32_LEAN_AND_MEAN for _Out_(?) and 
#include <initguid.h> // Required for __uuid it seems

#include <xaudio2.h>
#include <stdbool.h>

IXAudio2* pXAudio2 = 0;
IXAudio2MasteringVoice* pMasterVoice = 0;

void app_specific_init(void)
{
    HRESULT hr = {0};
    hr = CoInitializeEx(0, COINIT_MULTITHREADED );
    if (FAILED(hr))
    {  
        NL_LOG("Com Result failed to initialize");
        return;
    }

    if ( FAILED(hr = XAudio2Create( &pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR ) ) )
    {
        NL_LOG("XAudio 2 Create failed");
        return;
    }

    hr = IXAudio2_CreateMasteringVoice(
        pXAudio2, &pMasterVoice,
        XAUDIO2_DEFAULT_CHANNELS, 
        XAUDIO2_DEFAULT_SAMPLERATE, 
        0, NULL, NULL, 
        AudioCategory_GameEffects
    );

    if (FAILED(hr))
    {
        NL_LOG("Create Mastering Voice");
        return;
    }

    audio_data ad = {0};
    load_audio_data("Safe to Say - With Everything In Between - 09 Funeral.wav", &ad);
}

void app_specific_update(double dt)
{
    
}
