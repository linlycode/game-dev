#ifndef WINDOW_H
#define WINDOW_H

#include <functional>

#include "key_state.h"
#include "mouse_input.h"
#include "keyboard_keys.h"

struct SDL_Window;
union SDL_Event;

struct EventBase {
	double time; // in seconds
};

struct WindowSizeEvent : public EventBase {
	int width;
	int height;
};

struct MouseButtonEvent : public EventBase {
	MouseButton btn;
	KeyState state;
	int x;
	int y;
};

struct MouseMoveEvent : public EventBase {
	int x;
	int y;
};

struct KeyboardEvent : public EventBase {
	KeyboardKey key;
	KeyState state;
	int mods;
	bool isRepeat;
};

typedef std::function<void(WindowSizeEvent)> WindowSizeCallback;

typedef std::function<void(MouseButtonEvent)> MouseButtonCallback;

typedef std::function<void(MouseMoveEvent)> MouseMoveCallback;

typedef std::function<void(KeyboardEvent)> KeyboardKeyCallback;

class Window {
public:
	Window(const char *title, int width, int height);
	Window(const Window &other) = delete;
	~Window();

	void swapBuffers();

	void getSize(int &width, int &height) const;

	bool isKeyPressed(KeyboardKey key) const;

	void onResize(WindowSizeCallback);

	void onMouseButtonInput(MouseButtonCallback);

	void onMouseMove(MouseMoveCallback);

	void onKeyboardInput(KeyboardKeyCallback);

private:
	static int handleEvent(void *, SDL_Event *event);

private:
	SDL_Window *m_window;
	uint32_t m_id;
	void *m_ctx;
	WindowSizeCallback m_onResize;
	MouseButtonCallback m_onMouseBtnInput;
	MouseMoveCallback m_onMouseMove;
	KeyboardKeyCallback m_onKeyboardInput;
};

#endif
