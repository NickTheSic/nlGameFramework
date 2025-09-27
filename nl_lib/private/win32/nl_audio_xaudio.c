#include <private/nl_audio.h>
#include <private/nl_wave_file.h>
#include <private/win32/nl_win32_include.h>

#include <string.h>

/*
    * New TODOs
    Now that I know that the pBufferContext in the xAudioCallbacks is the pContext value in the struct
    I can now do more in-depth things with this system; 
    Including:
    - the ability to find and use the next available buffer so sounds can overlap if needed
    - Handle the sounds as I have where only one ever plays at once
    - Streaming audio from disk? 
        https://learn.microsoft.com/en-us/windows/win32/xaudio2/streaming-audio-data
        Could allow for 'pikmin' style changes by setting audio flags to trigger different tracks to play next

*/

// Thanks to https://github.com/tsherif/xaudio2-c-demo/ for the code reference using C instead of C++ (MIT License as of 2024-12-29 0:10)
typedef struct xaudio_loaded_sound xaudio_loaded_sound;
struct xaudio_loaded_sound
{
    WAVEFORMATEX format;
    unsigned int size;
    unsigned char* data;
    unsigned char is_playing;
};

typedef struct xaudio_volumes xaudio_volumes;
struct xaudio_volumes 
{
    float master;
    float sfx;
    float music;
};

typedef struct xaudio_audio_system xaudio_audio_system;
struct xaudio_audio_system 
{
    IXAudio2 *xaudio_engine;
    IXAudio2MasteringVoice *xaudio_mastering_voice;
    IXAudio2SourceVoice *xaudio_voices[MAX_SOUND_BUFFERS];
    xaudio_loaded_sound loaded_sounds[MAX_SOUND_BUFFERS];
    XAUDIO2_BUFFER xaudio_buffers[MAX_SOUND_BUFFERS];
    xaudio_volumes current_volumes;
    int currently_used_voices;
}; 
global_variable xaudio_audio_system *local_xaudio_system = 0;

// void* pBufferContext is the pContext that is in the XAUDIO2_BUFFER
// Super useful to know
void OnBufferEnd(IXAudio2VoiceCallback* This, void* pBufferContext) 
{
    NL_UNUSED(This);

    xaudio_loaded_sound* const voice = (xaudio_loaded_sound*)pBufferContext;
    voice->is_playing = 0;
    NL_LOG("XAudio::BufferEnd: pBufferContext is playing: %d", voice->is_playing);
}

void OnStreamEnd(IXAudio2VoiceCallback* This) 
{
    NL_UNUSED(This); 
    NL_LOG("On XAudio Stream End");
}

void OnVoiceProcessingPassEnd(IXAudio2VoiceCallback* This) 
{
    NL_UNUSED(This); 
    // Comment due to spam
    //NL_LOG("On XAudio Voice Processing Pass End");
}

void OnVoiceProcessingPassStart(IXAudio2VoiceCallback* This, UINT32 SamplesRequired) 
{
    NL_UNUSED(This); NL_UNUSED(SamplesRequired);
    // Comment due to spam
    //NL_LOG("On XAudio Voice Processing Pass Start");
}

void OnBufferStart(IXAudio2VoiceCallback* This, void* pBufferContext) 
{
    NL_UNUSED(This);
    
    xaudio_loaded_sound* const voice = (xaudio_loaded_sound*)pBufferContext;
    voice->is_playing = 1;
    NL_LOG("XAudio::BufferStart: pBufferContext is playing: %d", voice->is_playing);
}

void OnLoopEnd(IXAudio2VoiceCallback* This, void* pBufferContext) 
{
    NL_UNUSED(This); NL_UNUSED(pBufferContext);
    NL_LOG("On XAudio On Loop End");
}

// Might be the most important of the callbacks!
void OnVoiceError(IXAudio2VoiceCallback* This, void* pBufferContext, HRESULT Error) 
{
    NL_UNUSED(This); NL_UNUSED(pBufferContext); NL_UNUSED(Error); 
    NL_LOG("On XAudio Voice Error");
}

///////////////////////////////////////////////////////////////
// The trick to setting up callbacks in C is that the function
// pointers go in the 'lpVtbl' property, which is of type 
// IXAudio2VoiceCallbackVtbl*. (In C++, this is done by
// inheriting from IXAudio2VoiceCallback.)
///////////////////////////////////////////////////////////
IXAudio2VoiceCallback xAudioCallbacks = {
    .lpVtbl = &(IXAudio2VoiceCallbackVtbl) {
        .OnStreamEnd = OnStreamEnd,
        .OnVoiceProcessingPassEnd = OnVoiceProcessingPassEnd,
        .OnVoiceProcessingPassStart = OnVoiceProcessingPassStart,
        .OnBufferEnd = OnBufferEnd,
        .OnBufferStart = OnBufferStart,
        .OnLoopEnd = OnLoopEnd,
        .OnVoiceError = OnVoiceError
    }
};

int init_audio_system(void)
{
    NL_LOG("Initializing XAudio as audio system");

    HRESULT com_result ={0};
    com_result = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(com_result))
    {
	    NL_LOG("CoInitialize returned S_Failed but this can be caused by a previous call to the function so I am continuing execution of init_audio");
    }

    local_xaudio_system = (xaudio_audio_system*)memory_allocate(sizeof(xaudio_audio_system));
    if (0 == local_xaudio_system)
    {
        NL_LOG("Unable to allocate space for the local xaudio system");
        return 0;
    }

    const UINT32 flags = 0;
    com_result = XAudio2Create(&local_xaudio_system->xaudio_engine, flags, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(com_result))
	{
		NL_LOG("Failed to create xaudio2");
		return 0;
	}

    // Reference https://learn.microsoft.com/en-us/windows/win32/api/audiosessiontypes/ne-audiosessiontypes-audio_stream_category
    // The above will describe the AudioCategory. 
    // May need to init one for game fx and BGM
    com_result = IXAudio2_CreateMasteringVoice(
        local_xaudio_system->xaudio_engine, 
        &local_xaudio_system->xaudio_mastering_voice, 
        XAUDIO2_DEFAULT_CHANNELS, 
        XAUDIO2_DEFAULT_SAMPLERATE, 
        0, 
        0, 
        NULL, 
        AudioCategory_GameMedia
    );

	if (FAILED(com_result))
	{
		NL_LOG("Failed to create mastering voice");
		return 0;
	}

	return 1;
}

void cleanup_audio_system(void)
{   
    if (0 == local_xaudio_system)
    {
        CoUninitialize();
        return;
    }

    for (int i = 0; i < MAX_SOUND_BUFFERS; ++i)
    {
        if (local_xaudio_system->loaded_sounds[i].data != 0)
        {
            memory_free(local_xaudio_system->loaded_sounds[i].data);
        }

        if (local_xaudio_system->xaudio_voices[i] != 0)
        {
            IXAudio2SourceVoice_DestroyVoice(local_xaudio_system->xaudio_voices[i]);
        }
    }

    if (local_xaudio_system->xaudio_mastering_voice != 0)
    {
	    IXAudio2MasteringVoice_DestroyVoice(local_xaudio_system->xaudio_mastering_voice);
    }

    if (local_xaudio_system->xaudio_engine != 0)
	{
		IXAudio2_Release(local_xaudio_system->xaudio_engine);
	}
    memory_free(local_xaudio_system);

	CoUninitialize();
}


internal_function unsigned int load_wav_sound(const char* filename)
{
    if (local_xaudio_system->currently_used_voices >= MAX_SOUND_BUFFERS)
    {
        NL_LOG("Unable to load %s as currently used voices are greater than the max allowed", filename);
        return NL_INVALID_SOUND;
    }

    file_contents sound_file = {0};
    read_entire_file(filename, &sound_file);
    if (sound_file.size == 0)
    {
        NL_LOG("Unable to find sound file: %s", filename);
        return NL_INVALID_SOUND;
    }

    int current_voice = local_xaudio_system->currently_used_voices;

    wav_file_header* const header = (wav_file_header* const)(sound_file.content);
    xaudio_loaded_sound* const sound = &local_xaudio_system->loaded_sounds[current_voice];

    sound->data = memory_allocate(header->data_size);
    if (!sound->data)
    {
    	NL_LOG("unable to allocate data for xaudio sound %s", filename);
        clear_file_read(&sound_file);
        return NL_INVALID_SOUND;
    }
    
    memcpy(sound->data, sound_file.content+sizeof(wav_file_header), header->data_size);
    sound->size = header->data_size;

    sound->format.wFormatTag      = header->format;         /* format type */ // defined as WAVE_FORMAT_EXTENSIBLE in mmreg.h
    sound->format.nChannels       = header->channels;       /* number of channels (i.e. mono, stereo...) */
    sound->format.nSamplesPerSec  = header->sample_rate;     /* sample rate */
    sound->format.nAvgBytesPerSec = header->bytes_per_second; /* for buffer estimation */
    sound->format.nBlockAlign     = header->bytes_per_sample; /* block size of data */
    sound->format.wBitsPerSample  = header->bits_per_sample;  /* Number of bits per sample of mono data */
    sound->format.cbSize          = 0;                      /* The count in bytes of the size of*/

    clear_file_read(&sound_file);

    HRESULT source_result = IXAudio2_CreateSourceVoice
    (
    	local_xaudio_system->xaudio_engine,                 // This
    	&local_xaudio_system->xaudio_voices[current_voice], // souce voice
    	&sound->format,                // source format
    	0,                             // flags
    	XAUDIO2_DEFAULT_FREQ_RATIO,    //MaxFrequencyRatio
    	&xAudioCallbacks,              //xaudio callbacks
    	NULL,                          // SendList
    	NULL                           // Effect Chain
    );

    if (FAILED(source_result))
    {
    	NL_LOG("Failed to create source voice for %s", filename);
        memset(sound, 0, sizeof(xaudio_loaded_sound));
    	return NL_INVALID_SOUND;
    }

	source_result = IXAudio2SourceVoice_Start(local_xaudio_system->xaudio_voices[current_voice], 0, XAUDIO2_COMMIT_NOW);

    if (FAILED(source_result))
    {
        NL_LOG("Failed to start voice for %s", filename);
        //TODO: Some sort of error handling here
        return NL_INVALID_SOUND;
    }

    ++local_xaudio_system->currently_used_voices;
    NL_LOG("Successfully loaded %s in slot %d", filename, current_voice);

    return current_voice;
}

unsigned int load_sound_file(const char* const filename)
{
    const char* file_type = find_file_type_from_name(filename);

    if (strcmp(file_type, ".wav\n"))
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
        NL_LOG("Trying to play an Invalid Sound!");
        return;
    }

    xaudio_loaded_sound* const voice = &local_xaudio_system->loaded_sounds[sound];
    if (voice->is_playing == 1)
    {
        NL_LOG("Sound is already playing! Not playing again at this time");
        return;
    }
    voice->is_playing = 1;

    XAUDIO2_BUFFER* const buffer = &local_xaudio_system->xaudio_buffers[sound];
    IXAudio2SourceVoice* const source = local_xaudio_system->xaudio_voices[sound];

	buffer->AudioBytes = voice->size;
	buffer->pAudioData = voice->data;
	buffer->Flags = XAUDIO2_END_OF_STREAM;
    buffer->pContext = voice;

	//NOTE: Submit Source Buffer queues the audio to be streamed
    IXAudio2SourceVoice_SubmitSourceBuffer(source, buffer, NULL);
}

void set_sound_to_loop(unsigned int sound)
{
    if (sound == NL_INVALID_SOUND)
    {
        NL_LOG("Trying to loop an Invalid Sound!");
        return;
    }

    NL_LOG("Setting sound: %d to loop", sound);

    XAUDIO2_BUFFER* const buffer = &local_xaudio_system->xaudio_buffers[sound];
    buffer->LoopCount = XAUDIO2_LOOP_INFINITE;
}

void set_sfx_volume(float volume)
{
    NL_UNIMPLEMENTED_FUNC
    local_xaudio_system->current_volumes.sfx = volume * local_xaudio_system->current_volumes.master;
}

void set_music_volume(float volume)
{
    NL_UNIMPLEMENTED_FUNC
    local_xaudio_system->current_volumes.music = volume * local_xaudio_system->current_volumes.master;
}

void set_master_volume(float volume)
{
    if (volume > 1.0f)
    {
        NL_LOG("AUDIO: I plan to pass in the values 0 -> 1 for volume. If this is greater then I am dividing by 100 by default");
        volume /= 100.0f;
    }

    local_xaudio_system->current_volumes.master = volume;

    IXAudio2SourceVoice_SetVolume(local_xaudio_system->xaudio_mastering_voice, volume, XAUDIO2_COMMIT_NOW);
}
