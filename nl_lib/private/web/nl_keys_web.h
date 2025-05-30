

enum nl_key
{
    key_unkown =               0x0000, 
    key_escape =               0x0001,
    key_zero =                 0x0002,
    key_one =                  0x0003,
    key_two =                  0x0004,
    key_three =                0x0005,
    key_four =                 0x0006,
    key_five =                 0x0007,
    key_six =                  0x0008,
    key_seven =                0x0009,
    key_eight =                0x000A,
    key_nine =                 0x000B,
    key_minus =                0x000C,
    key_equal =                0x000D,
    key_backspace =            0x000E,
    key_tab =                  0x000F,
    key_q =                    0x0010,
    key_w =                    0x0011,
    key_e =                    0x0012,
    key_r =                    0x0013,
    key_t =                    0x0014,
    key_y =                    0x0015,
    key_u =                    0x0016,
    key_i =                    0x0017,
    key_o =                    0x0018,
    key_p =                    0x0019,
    key_bracketleft =          0x001A,
    key_bracketright =         0x001B,
    key_enter=                 0x001C,
    key_controlleft =          0x001D,
    key_a =                    0x001E, /* "KeyA"               */
    key_s =                    0x001F, /* "KeyS"               */
    key_d =                    0x0020, /* "KeyD"               */
    key_f =                    0x0021, /* "KeyF"               */
    key_g =                    0x0022, /* "KeyG"               */
    key_h =                    0x0023, /* "KeyH"               */
    key_j =                    0x0024, /* "KeyJ"               */
    key_k =                    0x0025, /* "KeyK"               */
    key_l =                    0x0026, /* "KeyL"               */
    key_semicolon =            0x0027, /* "Semicolon"          */
    key_quote =                0x0028, /* "Quote"              */
    key_backquote =            0x0029, /* "Backquote"          */
    key_shiftleft =            0x002A, /* "ShiftLeft"          */
    key_backslash =            0x002B, /* "Backslash"          */
    key_z =                    0x002C, /* "KeyZ"               */
    key_x =                    0x002D, /* "KeyX"               */
    key_c =                    0x002E, /* "KeyC"               */
    key_v =                    0x002F, /* "KeyV"               */
    key_b =                    0x0030, /* "KeyB"               */
    key_n =                    0x0031, /* "KeyN"               */
    key_m =                    0x0032, /* "KeyM"               */
    key_comma =                0x0033, /* "Comma"              */
    key_period =               0x0034, /* "Period"             */
    key_slash =                0x0035, /* "Slash"              */
    key_shift_right =          0x0036, /* "ShiftRight"         */
    key_numpad_multiply =      0x0037, /* "NumpadMultiply"     */
    key_altleft =              0x0038, /* "AltLeft"            */
    key_space =                0x0039, /* "Space"              */
    key_capslock =             0x003A, /* "CapsLock"           */
    key_f1 =                   0x003B, /* "F1"                 */
    key_f2 =                   0x003C, /* "F2"                 */
    key_f3 =                   0x003D, /* "F3"                 */
    key_f4 =                   0x003E, /* "F4"                 */
    key_f5 =                   0x003F, /* "F5"                 */
    key_f6 =                   0x0040, /* "F6"                 */
    key_f7 =                   0x0041, /* "F7"                 */
    key_f8 =                   0x0042, /* "F8"                 */
    key_f9 =                   0x0043, /* "F9"                 */
    key_f10 =                  0x0044, /* "F10"                */
    key_pause =                0x0045, /* "Pause"              */
    key_scrolllock =           0x0046, /* "ScrollLock"         */
    key_numpad7 =              0x0047, /* "Numpad7"            */
    key_numpad8 =              0x0048, /* "Numpad8"            */
    key_numpad9 =              0x0049, /* "Numpad9"            */
    key_numpadsubtract =       0x004A, /* "NumpadSubtract"     */
    key_numpad4 =              0x004B, /* "Numpad4"            */
    key_numpad5 =              0x004C, /* "Numpad5"            */
    key_numpad6 =              0x004D, /* "Numpad6"            */
    key_numpadadd =            0x004E, /* "NumpadAdd"          */
    key_numpad1 =              0x004F, /* "Numpad1"            */
    key_numpad2 =              0x0050, /* "Numpad2"            */
    key_numpad3 =              0x0051, /* "Numpad3"            */
    key_numpad0 =              0x0052, /* "Numpad0"            */
    key_numpaddecimal =        0x0053, /* "NumpadDecimal"      */

    key_alt =                  0x0056, /* Alt */

    key_up =                   0xE048,
    key_left =                 0xE04B,
    key_right =                0xE04D, 
    key_down =                 0xE050,

    NL_KEY_COUNT
};