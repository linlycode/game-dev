#include <SDL2/SDL.h>

#include "infra/fmt.h"
#include "window.h"

Window::Window(const char *title, int width, int height)
	: m_window(nullptr), m_id(0), m_ctx(nullptr), m_onResize(nullptr) {
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!m_window) {
		throw std::runtime_error(
			fmt::sprintf("failed to create window, %s", SDL_GetError()));
	}

	m_id = SDL_GetWindowID(m_window);
	SDL_AddEventWatch(handleEvent, this);

	m_ctx = SDL_GL_CreateContext(m_window);
	if (!m_ctx) {
		throw std::runtime_error(fmt::sprintf(
			"failed to create OpenGL context, %s", SDL_GetError()));
	}
}

Window::~Window() {
	if (m_ctx) {
		SDL_GL_DeleteContext(m_ctx);
	}

	if (m_window) {
		SDL_DestroyWindow(m_window);
	}
}

void Window::swapBuffers() { SDL_GL_SwapWindow(m_window); }

void Window::onResize(std::function<void(int, int)> cb) { m_onResize = cb; }

// return 1 to add the event to the event queue, 0 to drop from the event queue
int Window::handleEvent(void *data, SDL_Event *event) {
	if (event->type == SDL_WINDOWEVENT) {
		const SDL_WindowEvent &evt = event->window;
		Window *wnd = static_cast<Window *>(data);

		if (evt.windowID == wnd->m_id) {
			switch (evt.event) {
			case SDL_WINDOWEVENT_RESIZED:
				if (wnd->m_onResize) {
					wnd->m_onResize(evt.data1, evt.data2);
				}
				break;
			}
		}
	}
	return 1;
}
