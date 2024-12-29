#include <private/nl_audio.h>
#include <private/nl_wave_file.h>
#include <private/win32/nl_win32_include.h>

#include <string.h>

// Thanks to https://github.com/tsherif/xaudio2-c-demo/ for the code reference in C (MIT License as of 2024-12-29 0:10)

typedef struct xaudio_loaded_sound xaudio_loaded_sound;
struct xaudio_loaded_sound
{
    WAVEFORMATEX format;
    unsigned int size;
    unsigned char* data;
};

// typedef struct xaudio_audio_system xaudio_audio_system;
// struct xaudio_audio_system 
// {

// };

IXAudio2 *xaudio_engine = {0};
IXAudio2MasteringVoice *xaudio_mastering_voice = {0};
IXAudio2SourceVoice *xaudio_voices[MAX_SOUND_BUFFERS] = {0};
xaudio_loaded_sound loaded_sounds[MAX_SOUND_BUFFERS] = {0};
XAUDIO2_BUFFER xaudio_buffers[MAX_SOUND_BUFFERS] = {0};
int currently_used_voices = 0;

internal_function unsigned int load_wav_sound(const char* filename)
{
    if (currently_used_voices >= MAX_SOUND_BUFFERS)
    {
        NL_LOG("Unable to load file as currently used voices are greater than the max allowed");
        return NL_INVALID_SOUND;
    }

    file_contents sound_file = {0};
    read_entire_file(filename, &sound_file);
    if (sound_file.size == 0)
    {
        NL_LOG("Unable to open sound file: %s", filename);
        return NL_INVALID_SOUND;
    }

    wav_file_header* const header = (wav_file_header* const)(sound_file.content);
    xaudio_loaded_sound* const sound = &loaded_sounds[currently_used_voices];

    sound->data = memory_allocate(header->data_size);
    if (!sound->data)
    {
    	NL_LOG("unable to allocate data for xaudio");
        clear_file_read(&sound_file);
        return NL_INVALID_SOUND;
    }
    
    memcpy(sound->data, sound_file.content+sizeof(wav_file_header), header->data_size);

    sound->format.wFormatTag      = header->format;         /* format type */
    sound->format.nChannels       = header->channels;       /* number of channels (i.e. mono, stereo...) */
    sound->format.nSamplesPerSec  = header->sample_rate;     /* sample rate */
    sound->format.nAvgBytesPerSec = header->bytes_per_second; /* for buffer estimation */
    sound->format.nBlockAlign     = header->bytes_per_sample; /* block size of data */
    sound->format.wBitsPerSample  = header->bits_per_sample;  /* Number of bits per sample of mono data */
    sound->format.cbSize          = 0;                      /* The count in bytes of the size of*/

    clear_file_read(&sound_file);

    const HRESULT xaudio_createsource_result = IXAudio2_CreateSourceVoice
    (
    	xaudio_engine,                          // This
    	&xaudio_voices[currently_used_voices],  // souce voice
    	&sound->format,                         // source format
    	0,                                      // flags
    	XAUDIO2_DEFAULT_FREQ_RATIO,             //MaxFrequencyRatio
    	0,                                      //xaudio callbacks
    	NULL,                                   // SendList
    	NULL                                    // Effect Chain
    );

    if (FAILED(xaudio_createsource_result))
    {
    	NL_LOG("Failed to create source voice");
        memset(sound, 0, sizeof(xaudio_loaded_sound));
    	return NL_INVALID_SOUND;
    }

    int result = currently_used_voices;
    ++currently_used_voices;
    return result;
}

int init_audio_system(void)
{
    if (FAILED(CoInitializeEx(0, COINIT_MULTITHREADED)))
    {
	    NL_LOG("CoInitialize returned S_Failed but this can be caused by a previous call to the function so I am continuing execution of init_audio");
    }

    UINT32 flags = 0;
	if (FAILED(XAudio2Create(&xaudio_engine, flags, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		NL_LOG("Failed to create xaudio2");
		return 0;
	}

	if (FAILED(IXAudio2_CreateMasteringVoice(xaudio_engine, &xaudio_mastering_voice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL, 0)))
	{
		NL_LOG("Failed to create mastering voice");
		return 0;
	}

	return 1;
}

void cleanup_audio_system(void)
{   
    for (int i = 0; i < MAX_SOUND_BUFFERS; ++i)
    {
        if (xaudio_voices[i] != 0)
        {
            IXAudio2SourceVoice_DestroyVoice(xaudio_voices[i]);
        }
    }

    if (xaudio_mastering_voice != 0)
    {
	    IXAudio2MasteringVoice_DestroyVoice(xaudio_mastering_voice);
    }

    if (xaudio_engine != 0)
	{
		IXAudio2_Release(xaudio_engine);
	}

	CoUninitialize();
}

unsigned int load_sound_file(const char* const filename)
{
    const char* file_type = find_file_type_from_name(filename);

    if (strcmp(file_type, ".wav"))
    {
        return load_wav_sound(filename);
    }

    NL_LOG("No compatible audio type found for %s", file_type);
    return NL_INVALID_SOUND;
}

void play_sound(unsigned int sound)
{
    if (sound == NL_INVALID_SOUND)
    {
        NL_LOG("Trying to loop and Invalid Sound!");
        return;
    }

    xaudio_loaded_sound* const voice = &loaded_sounds[sound];
    XAUDIO2_BUFFER* const buffer = &xaudio_buffers[sound];
    IXAudio2SourceVoice* const source = xaudio_voices[sound];

	IXAudio2SourceVoice_Start(source, 0, XAUDIO2_COMMIT_NOW);

	buffer->AudioBytes = voice->size;
	buffer->pAudioData = voice->data;
	buffer->Flags = XAUDIO2_END_OF_STREAM;

	IXAudio2SourceVoice_SubmitSourceBuffer(source, buffer, NULL);
}

void set_sound_to_loop(unsigned int sound)
{
    if (sound == NL_INVALID_SOUND)
    {
        NL_LOG("Trying to loop and Invalid Sound!");
        return;
    }

    XAUDIO2_BUFFER* const buffer = &xaudio_buffers[sound];
    buffer->LoopCount = XAUDIO2_LOOP_INFINITE;
}

