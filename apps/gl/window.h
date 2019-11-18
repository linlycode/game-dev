#ifndef WINDOW_H
#define WINDOW_H

#include <functional>

struct SDL_Window;
union SDL_Event;

class Window {
public:
	Window(const char *title, int width, int height);
	Window(const Window &other) = delete;
	~Window();

	void swapBuffers();

	void onResize(std::function<void(int, int)> cb);

private:
	static int handleEvent(void *, SDL_Event *event);

private:
	SDL_Window *m_window;
	uint32_t m_id;
	void *m_ctx;
	std::function<void(int, int)> m_onResize;
};

#endif
