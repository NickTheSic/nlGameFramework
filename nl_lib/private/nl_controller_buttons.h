#ifndef __NL_CONTROLLER_BUTTONS_H__
#define __NL_CONTROLLER_BUTTONS_H__

// Opting for the western use of PS* Cross and Circle

// Can call the main to buttons
// PRIMARY
// SECONDARY
// for interact and enter

//PSP INDEXES
#if defined(PSP) 
#define NL_GAMEPAD_SELECT     0x00  //0x000001  //PSP SELECT
#define NL_GAMEPAD_START      0x01  //0x000008  //PSP START
#define NL_GAMEPAD_DPAD_UP    0x02  //0x000010  //PSP UP
#define NL_GAMEPAD_DPAD_RIGHT 0x03  //0x000020  //PSP RIGHT
#define NL_GAMEPAD_DPAD_DOWN  0x04  //0x000040  //PSP DOWN
#define NL_GAMEPAD_DPAD_LEFT  0x05  //0x000080  //PSP LEFT
#define NL_GAMEPAD_L          0x06  //0x000100  //PSP LTRIGGER
#define NL_GAMEPAD_R          0x07  //0x000200  //PSP RTRIGGER
#define NL_GAMEPAD_Y          0x08  //0x001000  //PSP TRIANGLE
#define NL_GAMEPAD_B          0x09  //0x002000  //PSP CIRCLE
#define NL_GAMEPAD_A          0x0A  //0x004000  //PSP CROSS
#define NL_GAMEPAD_X          0x0B  //0x008000  //PSP SQUARE


//copied from xinput_h
#elif defined(_WIN32)
#define NL_GAMEPAD_DPAD_UP          0x0001 //xinput up
#define NL_GAMEPAD_DPAD_DOWN        0x0002 //xinput down
#define NL_GAMEPAD_DPAD_LEFT        0x0004 //xinput left
#define NL_GAMEPAD_DPAD_RIGHT       0x0008 //xinput right
#define NL_GAMEPAD_START            0x0010 //xinput start
#define NL_GAMEPAD_SELECT           0x0020 //xinput back Could also be select button

//#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040 //xinput left thumb
//#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080 //xinput right thumb
#define NL_GAMEPAD_L    0x0100 //xinput left shoulder
#define NL_GAMEPAD_R    0x0200 //xinput right shoulder

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

#else
#warning No controller input bindings setup
#define NL_GAMEPAD_DPAD_LEFT	0
#define NL_GAMEPAD_DPAD_RIGHT	0
#define NL_GAMEPAD_DPAD_DOWN	0
#define NL_GAMEPAD_DPAD_UP		0
#define NL_GAMEPAD_Z			0
#define NL_GAMEPAD_R			0
#define NL_GAMEPAD_L			0
#define NL_GAMEPAD_A			0
#define NL_GAMEPAD_B			0
#define NL_GAMEPAD_X			0
#define NL_GAMEPAD_Y			0
#define NL_GAMEPAD_START	    0
#endif

#endif//__NL_CONTROLLER_BUTTONS_H__