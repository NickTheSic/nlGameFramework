#include "../nl_audio.h"
#include "../nl_debug.h"
#include "../nl_memory.h"
#include "../nl_utility.h"

// This could be included in fileio since it is strictly about loading audio.

// Might have to use a WaveformatEx instead of this when using xaudio
#pragma pack(push, 1)
typedef struct wav_file_header wav_file_header;
struct wav_file_header
{
    char RIFF[4];
    int  file_size;
    char WAVE[4];
    char fmt[4];
    int  header_size;

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

#include <string.h>

internal_function void load_wav(const char* const filename, audio_data* const ad)
{
    if (ad == 0) {return;} // required to surpress a warning even though I would want it to crash as this should be initialized.

    file_contents audio_content = {0};
    read_entire_file(filename, &audio_content);

    wav_file_header* file_header = (wav_file_header*)audio_content.content;

    if(file_header == 0)
    {
        NL_LOG("File header could not be obtained from audio_content.content");
        return;
    }

    ad->format = file_header->format;
    ad->channels = file_header->channels;
    ad->sample_rate = file_header->sample_rate;
    ad->bytes_per_second = file_header->bytes_per_second;
    ad->bits_per_sample = file_header->bits_per_sample;
    ad->data_size = file_header->data_size;
    ad->the_audio = memory_allocate(file_header->data_size);

    // Dislike the &file_header[1] but it was warning me about adding sizeof(wav_file_header)
    memcpy(ad->the_audio, &file_header[1], file_header->data_size);

    clear_file_read(&audio_content);
}

void load_audio_data(const char* const filename, audio_data* audio_data)
{
    const char* file_type = find_file_type_from_name(filename);

    if (strcmp(file_type, ".wav"))
    {
        load_wav(filename, audio_data);
    }

    else
    {
        NL_LOG("No compatible audio type found for %s", file_type);
    }
}
