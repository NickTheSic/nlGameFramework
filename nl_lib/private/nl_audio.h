#ifndef __NL_AUDIO_H__
#define __NL_AUDIO_H__

int init_audio_system(void); 
void cleanup_audio_system(void);

unsigned int load_sound_file(const char* const filename);

void play_sound(unsigned int sound);

#endif //__NL_AUDIO_H__