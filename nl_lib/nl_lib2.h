#ifndef __NL_LIB_2_H__
#define __NL_LIB_2_H__

// Just the important functions to implement per platform
// Or I am copying raylib, either or

/////////////////////////////////////////////////////////////////
//                        Window Functions                     //
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//                        Audio Functions                      //
/////////////////////////////////////////////////////////////////

// User Doesn't need, can hide in main
int init_audio_system(void);
void cleanup_audio_system(void);

unsigned int load_sound_file(const char*);
void play_sound(unsigned int);
void set_sound_to_loop(unsigned int);


/////////////////////////////////////////////////////////////////
//                        Gamepad Functions                    //
/////////////////////////////////////////////////////////////////

// User doesn't need, can hide in main
int init_gamepad_system(void);
void cleanup_gamepad_system(void);
void udpate_gamepad(void);

int get_pressed_buttons(unsigned char controller_id);
int is_button_pressed(unsigned char controller_index, int button);

/////////////////////////////////////////////////////////////////
//                        Memory Functions                     //
/////////////////////////////////////////////////////////////////
#if 0 // to find memory leaks
#define memory_allocate(s) _memory_allocate(s); NL_LOG("%s %d", __FILE__, __LINE__);
#else 
#define memory_allocate(s) _memory_allocate(s);
#endif
void *_memory_allocate(size_t size);
void memory_free(void* memory);

#endif//__NL_LIB_2_H__ 