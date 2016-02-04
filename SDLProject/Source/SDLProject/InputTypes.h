//====================================================================================================
// Filename:	InputTypes.h
// Created by:	Johnny Wu
// Description:	Constants for inputs that maps with SDL_Keycode.
//====================================================================================================
#ifndef _INPUTTYPES_H_
#define _INPUTTYPES_H_

#include "SDL.h"

namespace Keys
{
	const int ZERO			= SDLK_0;			// 0
	const int ONE			= SDLK_1;			// 1
	const int TWO			= SDLK_2;			// 2
	const int THREE			= SDLK_3;			// 3
	const int FOUR			= SDLK_4;			// 4
	const int FIVE			= SDLK_5;			// 5
	const int SIX			= SDLK_6;			// 6
	const int SEVEN			= SDLK_7;			// 7
	const int EIGHT			= SDLK_8;			// 8
	const int NINE			= SDLK_9;			// 9
	const int A				= SDLK_a;			// A
	const int B				= SDLK_b;			// B
	const int C				= SDLK_c;			// C
	const int D				= SDLK_d;			// D
	const int E				= SDLK_e;			// E
	const int F				= SDLK_f;			// F
	const int G				= SDLK_g;			// G
	const int H				= SDLK_h;			// H
	const int I				= SDLK_i;			// I
	const int J				= SDLK_j;			// J
	const int K				= SDLK_k;			// K
	const int L				= SDLK_l;			// L
	const int M				= SDLK_m;			// M
	const int N				= SDLK_n;			// N
	const int O				= SDLK_o;			// O
	const int P				= SDLK_p;			// P
	const int Q				= SDLK_q;			// Q
	const int R				= SDLK_r;			// R
	const int S				= SDLK_s;			// S
	const int T				= SDLK_t;			// T
	const int U				= SDLK_u;			// U
	const int V				= SDLK_v;			// V
	const int W				= SDLK_w;			// W
	const int X				= SDLK_x;			// X
	const int Y				= SDLK_y;			// Y
	const int Z				= SDLK_z;			// Z
	
	const int TILDE			= SDLK_BACKQUOTE;	// "`"
	const int QUOTE			= SDLK_QUOTE;		// "'"
	const int MINUS			= SDLK_MINUS;		// "-"
	const int EQUALS		= SDLK_EQUALS;		// "="
	const int LEFTBRACKET	= SDLK_LEFTBRACKET;	// "["
	const int RIGHTBRACKET	= SDLK_RIGHTBRACKET;// "]"
	const int BACKSLASH		= SDLK_BACKSLASH;	// "\"
	const int SEMICOLON		= SDLK_SEMICOLON;	// ";"
	const int COMMA			= SDLK_COMMA;		// ","
	const int PERIOD		= SDLK_PERIOD;		// "."
	const int SLASH			= SDLK_SLASH;		// "/"

	const int F1			= SDLK_F1;			// F1
	const int F2			= SDLK_F2;			// F2
	const int F3			= SDLK_F3;			// F3
	const int F4			= SDLK_F4;			// F4
	const int F5			= SDLK_F5;			// F5
	const int F6			= SDLK_F6;			// F6
	const int F7			= SDLK_F7;			// F7
	const int F8			= SDLK_F8;			// F8
	const int F9			= SDLK_F9;			// F9
	const int F10			= SDLK_F10;			// F10
	const int F11			= SDLK_F11;			// F11
	const int F12			= SDLK_F12;			// F12
	
	const int ESCAPE		= SDLK_ESCAPE;		// "Escape"	
	const int TAB			= SDLK_TAB;			// "Tab"
	const int CAPSLOCK		= SDLK_CAPSLOCK;	// "CapsLock"
	const int BACKSPACE		= SDLK_BACKSPACE;	// "Backspace"
	const int ENTER			= SDLK_RETURN;		// "Enter/Return"
	const int LALT			= SDLK_LALT;		// "Left Alt"
	const int LCTRL			= SDLK_LCTRL;		// "Left Ctrl"
	const int LSHIFT		= SDLK_LSHIFT;		// "Left Shift"
	const int SPACE			= SDLK_SPACE;		// "Space"
	const int RALT			= SDLK_RALT;		// "Right Alt"
	const int RCTRL			= SDLK_RCTRL;		// "Right Ctrl"
	const int RSHIFT		= SDLK_RSHIFT;		// "Right Shift"

	const int PRINTSCREEN	= SDLK_PRINTSCREEN;	// "PrintScreen"
	const int SCROLLLOCK	= SDLK_SCROLLLOCK;	// "ScrollLock"
	const int PAUSE			= SDLK_PAUSE;		// "Pause"
	
	const int INSERT		= SDLK_INSERT;		// "Insert"	
	const int HOME			= SDLK_HOME;		// "Home"
	const int PAGEUP		= SDLK_PAGEUP;		// "PageUp"
	const int DELETE		= SDLK_DELETE;		// "Delete"
	const int END			= SDLK_END;			// "End"
	const int PAGEDOWN		= SDLK_PAGEDOWN;	// "PageDown"
	
	const int UP			= SDLK_UP;			// "Up"
	const int DOWN			= SDLK_DOWN;		// "Down"
	const int LEFT			= SDLK_LEFT;		// "Left"
	const int RIGHT			= SDLK_RIGHT;		// "Right"

	const int NUMLOCKCLEAR	= SDLK_NUMLOCKCLEAR;// "Numlock"	
	const int KP_0			= SDLK_KP_0;		// "Keypad 0"
	const int KP_1			= SDLK_KP_1;		// "Keypad 1"
	const int KP_2			= SDLK_KP_2;		// "Keypad 2"
	const int KP_3			= SDLK_KP_3;		// "Keypad 3"
	const int KP_4			= SDLK_KP_4;		// "Keypad 4"
	const int KP_5			= SDLK_KP_5;		// "Keypad 5"
	const int KP_6			= SDLK_KP_6;		// "Keypad 6"
	const int KP_7			= SDLK_KP_7;		// "Keypad 7"
	const int KP_8			= SDLK_KP_8;		// "Keypad 8"
	const int KP_9			= SDLK_KP_9;		// "Keypad 9"
	const int KP_PLUS		= SDLK_KP_PLUS;		// "Keypad +"
	const int KP_MINUS		= SDLK_KP_MINUS;	// "Keypad -"
	const int KP_MULTIPLY	= SDLK_KP_MULTIPLY;	// "Keypad *"
	const int KP_DIVIDE		= SDLK_KP_DIVIDE;	// "Keypad /"
	const int KP_ENTER		= SDLK_KP_ENTER;	// "Keypad Enter"
	const int KP_PERIOD		= SDLK_KP_PERIOD;	// "Keypad ."

	const int MOUSE_L		= SDL_BUTTON_LEFT;	// "Left Mouse Button"
	const int MOUSE_M		= SDL_BUTTON_MIDDLE;// "Middle Mouse Button"
	const int MOUSE_R		= SDL_BUTTON_RIGHT;	// "Right Mouse Button"
}

#endif // #ifndef _INPUTTYPES_H_