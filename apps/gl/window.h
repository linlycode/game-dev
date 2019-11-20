#ifndef WINDOW_H
#define WINDOW_H

#include <functional>

#include "mouse_input.h"

struct SDL_Window;
union SDL_Event;

class Window {
public:
	Window(const char *title, int width, int height);
	Window(const Window &other) = delete;
	~Window();

	void swapBuffers();

	void getSize(int &width, int &height) const;

	void onResize(std::function<void(int, int)> cb);
	void onMouseDown(
		std::function<void(enum MouseButton btn, int x, int y)> cb);
	void onMouseUp(std::function<void(enum MouseButton btn, int x, int y)> cb);
	void onMouseMove(std::function<void(int, int)> cb);

private:
	static int handleEvent(void *, SDL_Event *event);

private:
	SDL_Window *m_window;
	uint32_t m_id;
	void *m_ctx;
	std::function<void(int, int)> m_onResize;
	std::function<void(MouseButton, int, int)> m_onMouseDown;
	std::function<void(MouseButton, int, int)> m_onMouseUp;
	std::function<void(int, int)> m_onMouseMove;
};

#endif
