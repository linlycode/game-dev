#ifndef KEYBOARD_KEYS_H
#define KEYBOARD_KEYS_H

#include <SDL2/SDL_keycode.h>

// clang-format off

enum KeyboardKey {
	KEY_ESC = SDL_SCANCODE_ESCAPE,
	KEY_F1 = SDL_SCANCODE_F1, KEY_F2 = SDL_SCANCODE_F2,
	KEY_F3 = SDL_SCANCODE_F3, KEY_F4 = SDL_SCANCODE_F4,
	KEY_F5 = SDL_SCANCODE_F5, KEY_F6 = SDL_SCANCODE_F6,
	KEY_F7 = SDL_SCANCODE_F7, KEY_F8 = SDL_SCANCODE_F8,
	KEY_F9 = SDL_SCANCODE_F9, KEY_F10 = SDL_SCANCODE_F10,
	KEY_F11 = SDL_SCANCODE_F11, KEY_F12 = SDL_SCANCODE_F12,

	KEY_BACKQUOTE = SDL_SCANCODE_GRAVE,
	KEY_1 = SDL_SCANCODE_1, KEY_2 = SDL_SCANCODE_2,
	KEY_3 = SDL_SCANCODE_3, KEY_4 = SDL_SCANCODE_4,
	KEY_5 = SDL_SCANCODE_5, KEY_6 = SDL_SCANCODE_6,
	KEY_7 = SDL_SCANCODE_7, KEY_8 = SDL_SCANCODE_8,
	KEY_9 = SDL_SCANCODE_9, KEY_0 = SDL_SCANCODE_0,
	KEY_MINUS = SDL_SCANCODE_MINUS,
	KEY_EQUAL = SDL_SCANCODE_EQUALS,
	KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,

	KEY_TAB = SDL_SCANCODE_TAB,
	KEY_Q = SDL_SCANCODE_Q, KEY_W = SDL_SCANCODE_W,
	KEY_E = SDL_SCANCODE_E, KEY_R = SDL_SCANCODE_R,
	KEY_T = SDL_SCANCODE_T, KEY_Y = SDL_SCANCODE_Y,
	KEY_U = SDL_SCANCODE_U, KEY_I = SDL_SCANCODE_I,
	KEY_O = SDL_SCANCODE_O, KEY_P = SDL_SCANCODE_P,
	KEY_LEFT_BRACKET = SDL_SCANCODE_LEFTBRACKET,
	KEY_RIGHT_BRACKET = SDL_SCANCODE_RIGHTBRACKET,
	KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,

	KEY_CAPS_LOCK = SDL_SCANCODE_CAPSLOCK,
	KEY_A = SDL_SCANCODE_A, KEY_S = SDL_SCANCODE_S, KEY_D = SDL_SCANCODE_D,
	KEY_F = SDL_SCANCODE_F, KEY_G = SDL_SCANCODE_G, KEY_H = SDL_SCANCODE_H,
	KEY_J = SDL_SCANCODE_J, KEY_K = SDL_SCANCODE_K, KEY_L = SDL_SCANCODE_L,
	KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
	KEY_SINGLE_QUOTE = SDL_SCANCODE_APOSTROPHE,
	KEY_ENTER = SDL_SCANCODE_RETURN,

	KEY_LEFT_SHIFT = SDL_SCANCODE_LSHIFT,
	KEY_Z = SDL_SCANCODE_Z, KEY_X = SDL_SCANCODE_X, KEY_C = SDL_SCANCODE_C,
	KEY_V = SDL_SCANCODE_V, KEY_B = SDL_SCANCODE_B, KEY_N = SDL_SCANCODE_N,
	KEY_M = SDL_SCANCODE_M,
	KEY_COMMA = SDL_SCANCODE_COMMA, KEY_PERIOD = SDL_SCANCODE_PERIOD,
	KEY_SLASH = SDL_SCANCODE_SLASH, KEY_RIGHT_SHIFT = SDL_SCANCODE_RSHIFT,

	KEY_LEFT_CTRL = SDL_SCANCODE_LCTRL, // 	KEY_FN =
	KEY_LEFT_COMMAND = SDL_SCANCODE_LGUI, KEY_LEFT_ALT = SDL_SCANCODE_LALT,
	KEY_SPACE = SDL_SCANCODE_SPACE,
	KEY_RIGHT_ALT = SDL_SCANCODE_RALT, KEY_RIGHT_COMMAND = SDL_SCANCODE_RGUI,
	KEY_MENU = SDL_SCANCODE_MENU, KEY_RIGHT_CTRL = SDL_SCANCODE_RCTRL,

	KEY_PRINT_SCREEN = SDL_SCANCODE_PRINTSCREEN,
	KEY_SCROLL_LOCK = SDL_SCANCODE_SCROLLLOCK,
	KEY_PAUSE = SDL_SCANCODE_PAUSE,

	KEY_INSERT = SDL_SCANCODE_INSERT, KEY_HOME = SDL_SCANCODE_HOME, KEY_PAGE_UP = SDL_SCANCODE_PAGEUP,
	KEY_DELETE = SDL_SCANCODE_DELETE, KEY_END = SDL_SCANCODE_END, KEY_PAGE_DOWN = SDL_SCANCODE_PAGEDOWN,

	KEY_UP = SDL_SCANCODE_UP, KEY_LEFT = SDL_SCANCODE_LEFT,
	KEY_DOWN = SDL_SCANCODE_DOWN, KEY_RIGHT = SDL_SCANCODE_RIGHT,

	KEY_NUM_LOCK = SDL_SCANCODE_NUMLOCKCLEAR, KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
	KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY, KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS,
	KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS, KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER,
	KEY_KP_DECIMAL = SDL_SCANCODE_KP_DECIMAL,

	KEY_KP_0 = SDL_SCANCODE_KP_0, KEY_KP_1 = SDL_SCANCODE_KP_1,
	KEY_KP_2 = SDL_SCANCODE_KP_2, KEY_KP_3 = SDL_SCANCODE_KP_3,
	KEY_KP_4 = SDL_SCANCODE_KP_4, KEY_KP_5 = SDL_SCANCODE_KP_5,
	KEY_KP_6 = SDL_SCANCODE_KP_6, KEY_KP_7 = SDL_SCANCODE_KP_7,
	KEY_KP_8 = SDL_SCANCODE_KP_8, KEY_KP_9 = SDL_SCANCODE_KP_9
};

enum ModifierKey {
	MOD_NONE = 0,
	MOD_LEFT_CTRL = KMOD_LCTRL, MOD_RIGHT_CTRL = KMOD_RCTRL,
	MOD_LEFT_SHIFT = KMOD_LSHIFT, MOD_RIGHT_SHIFT = KMOD_RSHIFT,
	MOD_LEFT_ALT = KMOD_LALT, MOD_RIGHT_ALT = KMOD_RALT,
	MOD_LEFT_COMMAND = KMOD_LGUI, MOD_RIGHT_COMMAND = KMOD_RGUI,
	// MOD_FN = 256,
	MOD_CAPS_LOCK = KMOD_CAPS, MOD_NUM_LOCK = KMOD_NUM,

	MOD_CTRL = MOD_LEFT_CTRL | MOD_RIGHT_CTRL,
	MOD_SHIFT = MOD_LEFT_SHIFT | MOD_RIGHT_SHIFT,
	MOD_ALT = MOD_LEFT_SHIFT | MOD_RIGHT_SHIFT,
	MOD_COMMAND = MOD_LEFT_COMMAND | MOD_RIGHT_COMMAND
};

// clang-format on

#endif
