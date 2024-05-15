#include "nl_lib.h"

#include "open_al.h"

#include "include/al.h"
#include "include/alc.h"

ALCdevice *audio_device = {0};
ALCcontext *audio_context = {0};

#define MAX_SOUND_BUFFERS 3
ALuint sound_buffers[MAX_SOUND_BUFFERS] = {0};
int _next_free_sound_in_buffer = 0;

ALuint song_sound = 0;
ALuint sfx_sound = 0;

static void print_audio_device_name(void)
{
    const ALCchar* name = 0;
    if (alcIsExtensionPresent(audio_device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(audio_device, ALC_ALL_DEVICES_SPECIFIER);
    }
    if (!name || alcGetError(audio_device) != ALC_NO_ERROR)
    {
        name = alcGetString(audio_device, ALC_DEVICE_SPECIFIER);
    }
    NL_LOG("Opened %s", name);
}

static ALuint load_sound(const char* filename)
{
    if (_next_free_sound_in_buffer >= MAX_SOUND_BUFFERS-1)
    {
        NL_LOG("Unable to allocate more sounds for this buffer.  We have reached the max sounds and can't load %s", filename);
        return 0;
    }

    file_contents sound_file = {0};
    read_entire_file(filename, &sound_file);
    if (sound_file.size == 0)
    {
        NL_LOG("Unable to open sound file: %s", filename);
        return 0;
    }

    wav_file_header * const wav_header = (wav_file_header* const)(sound_file.content);
    const short channels = wav_header->channels;
    const short bits_per_sample = wav_header->bits_per_sample;
    const int data_size = wav_header->data_size;
    const int sample_rate = wav_header->sample_rate;

    ALenum format = {0};
    if (channels == 1 &&  bits_per_sample == 8){
        format = AL_FORMAT_MONO8;
    }
    else if(channels == 1 && bits_per_sample == 16){   
        format = AL_FORMAT_MONO16;
    }
    else if(channels == 2 && bits_per_sample == 8){
        format = AL_FORMAT_STEREO8;
    }
    else if(channels == 2 && bits_per_sample == 16){
        format = AL_FORMAT_STEREO16;
    }   
    else{
        NL_LOG("Unable to deduce the format of the audio file");
    }

    alBufferData(sound_buffers[_next_free_sound_in_buffer],
                format, 
                (const ALvoid*)(sound_file.content+sizeof(wav_file_header)),
                data_size,
                sample_rate
                );

    clear_file_read(&sound_file);

    ALuint source;
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcei(source, AL_BUFFER, sound_buffers[_next_free_sound_in_buffer]);

    ++_next_free_sound_in_buffer;

    //ALint state = AL_PLAYING;
    //while(state == AL_PLAYING)
    //{
    //    alGetSourcei(source, AL_SOURCE_STATE, &state);
    //}
    //alDeleteSources(1, &source);

    return source;
}

void app_specific_init(void)
{
    audio_device = alcOpenDevice(0);
    if (audio_device == 0)
    {
        NL_LOG("Unable to create audio device");
    }
    
    audio_context = alcCreateContext(audio_device, 0);
    if (audio_context == 0)
    {
        NL_LOG("Unable to create audio context");
    }

    if (!alcMakeContextCurrent(audio_context))
    {
        NL_LOG("Unable to make audio context current");
    }
    print_audio_device_name();

    alGenBuffers(MAX_SOUND_BUFFERS, sound_buffers);

    song_sound = load_sound("data/StS_Funeral.wav");
    sfx_sound = load_sound("data/retrogamesfx.wav");

    alSourcePlay(song_sound);
}

void app_specific_update(double dt)
{
    if (was_key_pressed(key_space))
    {
        alSourcePlay(sfx_sound);
    }
}

void app_specific_cleanup(void)
{
    alDeleteBuffers(MAX_SOUND_BUFFERS, sound_buffers);

    if (song_sound != 0)
    {
        alDeleteSources(1, &song_sound);
    }

    alcMakeContextCurrent(0);
    alcDestroyContext(audio_context);

    ALCboolean closed = alcCloseDevice(audio_device);
}
