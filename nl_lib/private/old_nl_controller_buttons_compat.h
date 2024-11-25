#ifndef __OLD_NL_CONTROLLER_BUTTONS_COMPAT_H__
#define __OLD_NL_CONTROLLER_BUTTONS_COMPAT_H__

// The values listed here are the values as defined in their respective SDKS

// Keeping around in case I go back to this but at the moment it is not used how I expected

// This may not be working how I was hoping it would
// I wanted to standardize the names and their respective values
// But handling input like I do with keyboard and mouse does not work the same with PSP
// better to have them index in the order of bytes maybe

// Opting for the western use of PS* Cross and Circle

// Can call the main to buttons
// PRIMARY
// SECONDARY
// for interact and enter

//copied from pspctrl_h
#if defined(PSP) 
#define NL_GAMEPAD_SELECT        0x000001  //PSP SELECT
#define NL_GAMEPAD_START         0x000008  //PSP START
#define NL_GAMEPAD_DPAD_UP       0x000010  //PSP UP
#define NL_GAMEPAD_DPAD_RIGHT    0x000020  //PSP RIGHT
#define NL_GAMEPAD_DPAD_DOWN     0x000040  //PSP DOWN
#define NL_GAMEPAD_DPAD_LEFT     0x000080  //PSP LEFT
#define NL_GAMEPAD_L             0x000100  //PSP LTRIGGER
#define NL_GAMEPAD_R             0x000200  //PSP RTRIGGER
#define NL_GAMEPAD_Y             0x001000  //PSP TRIANGLE
#define NL_GAMEPAD_B             0x002000  //PSP CIRCLE
#define NL_GAMEPAD_A             0x004000  //PSP CROSS
#define NL_GAMEPAD_X             0x008000  //PSP SQUARE

//copied from libogc pad.h
#elif defined(GCN_GEKKO)
#define NL_GAMEPAD_DPAD_LEFT		0x0001 //gamecube left
#define NL_GAMEPAD_DPAD_RIGHT		0x0002 //gamecube right
#define NL_GAMEPAD_DPAD_DOWN	    0x0004 //gamecube down
#define NL_GAMEPAD_DPAD_UP			0x0008 //gamecube up
#define NL_GAMEPAD_Z			    0x0010 //gamecube z
#define NL_GAMEPAD_R			    0x0020 //gamecube r
#define NL_GAMEPAD_L			    0x0040 //gamecube l 
#define NL_GAMEPAD_A			    0x0100 //gamecube a
#define NL_GAMEPAD_B			    0x0200 //gamecube b
#define NL_GAMEPAD_X			    0x0400 //gamecube x
#define NL_GAMEPAD_Y			    0x0800 //gamecube y
#define NL_GAMEPAD_START		    0x1000 //gamecube start

//copoied from libogc wpad
#elif defined(WII_GEKKO)
#define NL_GAMEPAD_Y			    0x0001       //wii 2
#define NL_GAMEPAD_X			    0x0002       //wii 1
#define NL_GAMEPAD_B			    0x0004       //wii b
#define NL_GAMEPAD_A			    0x0008       //wii a
#define NL_GAMEPAD_SELECT		    0x0010       //wii -
//#define WPAD_BUTTON_HOME		    0x0080       //wii home
#define NL_GAMEPAD_DPAD_LEFT	    0x0100       //wii left
#define NL_GAMEPAD_DPAD_RIGHT	    0x0200       //wii right
#define NL_GAMEPAD_DPAD_DOWN	    0x0400       //wii down
#define NL_GAMEPAD_DPAD_UP		    0x0800       //wii up
#define NL_GAMEPAD_START		    0x1000       //wii +	
#define NL_GAMEPAD_L	            (0x0001<<16) //nunchuck z
#define NL_GAMEPAD_R	            (0x0002<<16) //nunchuck c

// copied from calico gba
#elif defined(NDS)
#define NL_GAMEPAD_A                 (1U<<0)  //nds a
#define NL_GAMEPAD_B                 (1U<<1)  //nds b
#define NL_GAMEPAD_SELECT            (1U<<2)  //nds select
#define NL_GAMEPAD_START             (1U<<3)  //nds start
#define NL_GAMEPAD_DPAD_RIGHT        (1U<<4)  //nds right
#define NL_GAMEPAD_DPAD_LEFT         (1U<<5)  //nds left
#define NL_GAMEPAD_DPAD_UP           (1U<<6)  //nds up
#define NL_GAMEPAD_DPAD_DOWN         (1U<<7)  //nds down
#define NL_GAMEPAD_R                 (1U<<8)  //nds r
#define NL_GAMEPAD_L                 (1U<<9)  //nds l
#define NL_GAMEPAD_X                 (1U<<10) //nds x
#define NL_GAMEPAD_Y                 (1U<<11) //nds y
//#define KEY_HINGE             (1U<<12) //nds hinge
//#define KEY_DEBUG             (1U<<13) //nds debug

//copied from xinput_h
#elif defined(_WIN32)
#define NL_GAMEPAD_DPAD_UP          0x0001 //xinput up
#define NL_GAMEPAD_DPAD_DOWN        0x0002 //xinput down
#define NL_GAMEPAD_DPAD_LEFT        0x0004 //xinput left
#define NL_GAMEPAD_DPAD_RIGHT       0x0008 //xinput right
#define NL_GAMEPAD_START            0x0010 //xinput start
#define NL_GAMEPAD_SELECT            0x0020 //xinput back Could also be select button

//#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040 //xinput left thumb
//#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080 //xinput right thumb
#define NL_GAMEPAD_L    0x0100 //xinput left shoulder
#define NL_GAMEPAD_R   0x0200 //xinput right shoulder

#define NL_GAMEPAD_A                0x1000 //xinput a
#define NL_GAMEPAD_B                0x2000 //xinput b
#define NL_GAMEPAD_X                0x4000 //xinput x
#define NL_GAMEPAD_Y                0x8000 //xinput y

// NO CONTROLLER in a browser... at least not that I know of
#elif defined(__EMSCRIPTEN__)
#define NL_GAMEPAD_DPAD_LEFT	
#define NL_GAMEPAD_DPAD_RIGHT	
#define NL_GAMEPAD_DPAD_DOWN	
#define NL_GAMEPAD_DPAD_UP		
#define NL_GAMEPAD_Z			
#define NL_GAMEPAD_R			
#define NL_GAMEPAD_L			
#define NL_GAMEPAD_A			
#define NL_GAMEPAD_B			
#define NL_GAMEPAD_X			
#define NL_GAMEPAD_Y			
#define NL_GAMEPAD_START		

//#elif defined(__GBA__)
// Not sure if I should use libtonc or libgba or skip this entirely
#else
#warning No controller input bindings setup
#endif

#endif//__NL_CONTROLLER_BUTTONS_H__