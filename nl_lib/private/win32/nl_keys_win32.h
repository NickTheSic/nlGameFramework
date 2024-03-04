#ifndef __NL_KEYS_WIN32_H__
#define __NL_KEYS_WIN32_H__

enum nl_key
{
    key_backspace = 0x08,
    key_tab       = 0x09,

    key_clear     = 0x0C,
    key_enter     = 0x0D,

    key_shift     = 0x10,
    key_control   = 0x11,
    key_alt       = 0x12,
    key_pause     = 0x13,
    key_capslock  = 0x14,

    // japanese keys

    key_escape    = 0x1B,

    key_space     = 0x20,
    key_pageup    = 0x21,
    key_pagedown  = 0x22,
    key_end       = 0x23,
    key_home      = 0x24,

    key_left        = 0x25,
    key_up          = 0x26,
    key_right       = 0x27,
    key_down        = 0x28,
    
    key_select      = 0x29,//	SELECT key
    key_print       = 0x2A,//PRINT key
    key_execute     = 0x2B,//EXECUTE key
    key_printscreen = 0x2C,//PRINT SCREEN key
    key_insert      = 0x2D,//	INS key
    key_delete      = 0x2E,//	DEL key
    key_help        = 0x2F,//	HELP key

    key_zero = 0x30,
	key_one = 0x31,
	key_two = 0x32,
	key_three = 0x33,
	key_four = 0x34,
	key_five = 0x35,
	key_six = 0x36,
	key_seven = 0x37,
	key_eight = 0x38,
	key_nine = 0x39,

    key_a = 0x41,
    key_b = 0x42,
    key_c = 0x43,
    key_d = 0x44,
    key_e = 0x45,
    key_f = 0x46,
    key_g = 0x47,
    key_h = 0x48,
    key_i = 0x49,
    key_j = 0x4A,
    key_k = 0x4B,
    key_l = 0x4C,
    key_m = 0x4D,
    key_n = 0x4E,
    key_o = 0x4F,
    key_p = 0X50,
    key_q = 0X51,
    key_r = 0X52,
    key_s = 0X53,
    key_t = 0X54,
    key_u = 0X55,
    key_v = 0X56,
    key_w = 0X57,    
    key_x = 0X58,    
    key_y = 0X59,    
    key_z = 0X5A,   

    // windows key left and right... also command on mac and super on linux

    key_numpad0 = 0x60,
    key_numpad1 = 0x61,
    key_numpad2 = 0x62,
    key_numpad3 = 0x63,
    key_numpad4 = 0x64,
    key_numpad5 = 0x65,
    key_numpad6 = 0x66,
    key_numpad7 = 0x67,
    key_numpad8 = 0x68,
    key_numpad9 = 0x69, 

    // TODO: Continue below starting with VK_MULTIPLY

    key_lcontrol = 0xA2,
    key_rcontrol = 0xA3,

    NL_KEY_COUNT
};

#endif