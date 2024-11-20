#ifndef __NL_WAVE_FILE_H__
#define __NL_WAVE_FILE_H__

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

#endif//__NL_WAVE_FILE_H__