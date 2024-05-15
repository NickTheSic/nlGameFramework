#ifndef __NL_AUDIO_H__
#define __NL_AUDIO_H__

int init_audio_system(void); 
void cleanup_audio_system(void);

unsigned int load_sound_file(const char* const filename);

#endif //__NL_AUDIO_H__