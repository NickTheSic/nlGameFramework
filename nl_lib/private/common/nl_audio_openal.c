#include "../nl_audio.h"

#include "../nl_debug.h"
#include "../nl_fileio.h"
#include "../nl_memory.h"

#include "string.h" // for strcmp

#include "../../third_party/al.h"
#include "../../third_party/alc.h"

// a helper struct to get the information by casting the file ptr to this
#pragma pack(push, 1)
typedef struct wav_file_header wav_file_header;
struct wav_file_header
{
    char RIFF[4];

    int  file_size;
    char WAVE[4];
    char fmt[4];

    int  header_size; // May be different on OSX
    
    short format;
    short channels;
    int sample_rate;
    int bytes_per_second;
    short bytes_per_sample;
    short bits_per_sample;
    
    char data_header[4];

    int data_size;
};
#pragma pack(pop)

#define MAX_SOUND_BUFFERS 3

typedef struct audio_system audio_system;
struct audio_system
{
    ALCdevice*  device;
    ALCcontext* context;

    int sounds_loaded; // buffers and sounds that have been used 

    ALuint *buffers;
    ALuint *sounds;
};
global_variable audio_system *local_audio_system = {0};

static void print_audio_device_name(void)
{
    const ALCchar* name = 0;

    if (alcIsExtensionPresent(local_audio_system->device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(local_audio_system->device, ALC_ALL_DEVICES_SPECIFIER);
    }

    if (!name || alcGetError(local_audio_system->device) != ALC_NO_ERROR)
    {
        name = alcGetString(local_audio_system->device, ALC_DEVICE_SPECIFIER);
    }

    NL_LOG("Opened %s for sound", name);
}

static ALuint load_wav_sound(const char* filename)
{
    if (local_audio_system == 0)
    {
        NL_LOG("Audio system isn't initialized cannot load a sound");
        return 0;
    }

    if (local_audio_system->sounds_loaded >= MAX_SOUND_BUFFERS-1)
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
    if (channels == 1 &&  bits_per_sample == 8)
    {
        format = AL_FORMAT_MONO8;
    }
    else if(channels == 1 && bits_per_sample == 16)
    {   
        format = AL_FORMAT_MONO16;
    }
    else if(channels == 2 && bits_per_sample == 8)
    {
        format = AL_FORMAT_STEREO8;
    }
    else if(channels == 2 && bits_per_sample == 16)
    {
        format = AL_FORMAT_STEREO16;
    }   
    else
    {
        NL_LOG("Unable to deduce the format of the audio file");
    }

    alBufferData(local_audio_system->buffers[local_audio_system->sounds_loaded],
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
    alSourcei(source, AL_BUFFER, local_audio_system->buffers[local_audio_system->sounds_loaded]);

    local_audio_system->sounds[local_audio_system->sounds_loaded] = source;
    ++local_audio_system->sounds_loaded;

    return source;
}

unsigned int load_sound_file(const char* filename)
{
    const char* file_type = find_file_type_from_name(filename);

    if (strcmp(file_type, ".wav"))
    {
        return load_wav_sound(filename);
    }

    NL_LOG("No compatible audio type found for %s", file_type);
    return 0;
}

int init_audio_system(void)
{
    local_audio_system = (audio_system*)memory_allocate(sizeof(audio_system));
    
    if (local_audio_system == 0)
    {
        NL_LOG("Unable to allocate memory for the audio system");
        return 0;
    }

    local_audio_system->buffers = (ALuint*)memory_allocate(sizeof(ALuint)*MAX_SOUND_BUFFERS);
    local_audio_system->sounds  = (ALuint*)memory_allocate(sizeof(ALuint)*MAX_SOUND_BUFFERS);

    local_audio_system->device = alcOpenDevice(0);
    if (local_audio_system->device == 0)
    {
        NL_LOG("Unable to create audio device");
        return 0;
    }
    
    local_audio_system->context = alcCreateContext(local_audio_system->device, 0);
    if (local_audio_system->context == 0)
    {
        NL_LOG("Unable to create audio context");
        return 0;
    }

    if (!alcMakeContextCurrent(local_audio_system->context))
    {
        NL_LOG("Unable to make audio context current");
        return 0;
    }

    print_audio_device_name();

    alGenBuffers(MAX_SOUND_BUFFERS, local_audio_system->buffers);

    return 1;
}

void cleanup_audio_system(void)
{
    if (local_audio_system != 0)
    {
        alDeleteBuffers(MAX_SOUND_BUFFERS, local_audio_system->buffers);
        alDeleteSources(local_audio_system->sounds_loaded, local_audio_system->buffers);

        alcMakeContextCurrent(0);
        alcDestroyContext(local_audio_system->context);

        alcCloseDevice(local_audio_system->device);

        if (local_audio_system->buffers != 0)
        {
            memory_free(local_audio_system->buffers);
        }

        if (local_audio_system->sounds  != 0)
        {
            memory_free(local_audio_system->sounds );
        }
        memory_free(local_audio_system);
    }
}

void play_sound(unsigned int sound)
{
    alSourcePlay(sound);
}

void set_sound_to_loop(unsigned int sound)
{
    alSourcei(sound, AL_LOOPING, AL_TRUE);
}