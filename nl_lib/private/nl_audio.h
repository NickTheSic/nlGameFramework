#ifndef __NL_AUDIO_H__
#define __NL_AUDIO_H__
#ifdef __cplusplus
extern "C" {
#endif


typedef struct audio_data audio_data; 
struct audio_data
{
	short format;
	short channels;
	int sample_rate;
	int bytes_per_second;
	short bytes_per_sample; // ^^ One of these is not needed? vv
	short bits_per_sample;

    int data_size;

	char* the_audio;
};


void load_audio_data(const char *const filename, audio_data* audio_data);


#ifdef __cplusplus
}
#endif
#endif //__NL_AUDIO_H__