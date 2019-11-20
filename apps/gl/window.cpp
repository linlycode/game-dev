#include <iostream>
#include <SDL2/SDL.h>

#include "infra/fmt.h"
#include "window.h"

namespace {
	MouseButton get_mouse_button(uint8_t btn) {
		switch (btn) {
			case SDL_BUTTON_LEFT:
				return MOUSE_BUTTON_LEFT;
			case SDL_BUTTON_MIDDLE:
				return MOUSE_BUTTON_MIDDLE;
			case SDL_BUTTON_RIGHT:
				return MOUSE_BUTTON_MIDDLE;
			default:
				throw std::domain_error(
					fmt::sprintf("unhandled mouse button %d", btn));
		}
	}
} // namespace

Window::Window(const char *title, int width, int height)
	: m_window(nullptr), m_id(0), m_ctx(nullptr), m_onResize(nullptr),
	  m_onMouseDown(nullptr), m_onMouseUp(nullptr), m_onMouseMove(nullptr) {
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

void Window::getSize(int &width, int &height) const {
	SDL_GetWindowSize(m_window, &width, &height);
}

void Window::onResize(std::function<void(int, int)> cb) { m_onResize = cb; }

void Window::onMouseDown(std::function<void(enum MouseButton, int, int)> cb) {
	m_onMouseDown = cb;
}

void Window::onMouseUp(std::function<void(enum MouseButton, int, int)> cb) {
	m_onMouseUp = cb;
}

void Window::onMouseMove(std::function<void(int, int)> cb) {
	m_onMouseMove = cb;
}

// return 1 to add the event to the event queue, 0 to drop from the event queue
int Window::handleEvent(void *data, SDL_Event *event) {
	Window *wnd = static_cast<Window *>(data);

	switch (event->type) {
		case SDL_WINDOWEVENT: {
			const SDL_WindowEvent &evt = event->window;

			if (evt.windowID == wnd->m_id) {
				switch (evt.event) {
					case SDL_WINDOWEVENT_RESIZED:
						if (wnd->m_onResize) {
							wnd->m_onResize(evt.data1, evt.data2);
						}
						break;
				}
			}

			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			const SDL_MouseButtonEvent &evt = event->button;
			if (evt.which != SDL_TOUCH_MOUSEID && evt.windowID == wnd->m_id) {
				if (wnd->m_onMouseDown) {
					wnd->m_onMouseDown(
						get_mouse_button(evt.button), evt.x, evt.y);
				}
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			const SDL_MouseButtonEvent &evt = event->button;
			if (evt.which != SDL_TOUCH_MOUSEID && evt.windowID == wnd->m_id) {
				if (wnd->m_onMouseUp) {
					wnd->m_onMouseUp(
						get_mouse_button(evt.button), evt.x, evt.y);
				}
			}
			break;
		}
		case SDL_MOUSEMOTION: {
			const SDL_MouseMotionEvent &evt = event->motion;
			if (evt.which != SDL_TOUCH_MOUSEID && evt.windowID == wnd->m_id) {
				if (wnd->m_onMouseMove) {
					wnd->m_onMouseMove(evt.x, evt.y);
				}
			}
		}
	}
	return 1;
}
