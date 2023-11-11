#include "nl_lib.h"

// Using VS2022 seems like the right play here with C so I can use intellisense
#include <windows.h> // required without WIN32_LEAN_AND_MEAN for _Out_(?) and 
#include <initguid.h> // Required for __uuid it seems

#include <xaudio2.h>
#include <stdbool.h>

IXAudio2* pXAudio2 = 0;
IXAudio2MasteringVoice* pMasterVoice = 0;


#pragma pack(push, 1)
typedef struct wav_file_header wav_file_header;
struct wav_file_header
{
    union
    {
        char RIFF[4];
        struct
        {
            char R, I, F1, F2;
        };
    };
    int  fileSize;
    union
    {
        struct
        {
            char W, A, V, E;
        };
        char WAVE[4];
    };
    union
    {
        char fmt[4];
        struct
        {
            char f, m, t, space;
        };
    };
    int  headerSize;
    
    short format;
    short channels;
    int sampleRate;
    int bytesPerSecond;
    short bytesPerSample;
    short bitsPerSample;
    
    union
    {
        char dataHeader[4];
        struct
        {
            char D, A1, T, A2;
        };
    };
    
    int dataSize;
};
#pragma pack(pop)

typedef struct audio_data audio_data;
struct audio_data
{
// Care about this stuff
	short format;
	short channels;
	int sampleRate;
	int bytesPerSecond;
	short bytesPerSample;
	short bitsPerSample;

	char* the_audio;
};

void load_wav(const char* filename/*, wav_data* wav*/)
{
    file_contents audio_content = {0};
    read_entire_file(filename, &audio_content);

    char* buffer = audio_content.content;
    wav_file_header* file_header = (wav_file_header*)buffer;

    char* the_audio = memory_allocate(file_header->dataSize);
    memcpy(the_audio, buffer+sizeof(wav_file_header), file_header->dataSize);

    clear_file_read(&audio_content);
}

extern void app_specific_init(void)
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

    hr = IXAudio2_CreateMasteringVoice(pXAudio2, &pMasterVoice,
        XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, NULL, NULL, AudioCategory_GameEffects);
    if (FAILED(hr))
    {
        NL_LOG("Create Mastering Voice");
        return;
    }

    load_wav("Safe to Say - With Everything In Between - 09 Funeral.wav");
}

extern void app_specific_update(double dt)
{
    
}
