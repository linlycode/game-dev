#include <iostream>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

#include "infra/fmt.h"
#include "window.h"

Window::Window(const char *title, int width, int height)
	: m_window(nullptr), m_id(0), m_ctx(nullptr), m_onResize(nullptr),
	  m_onMouseBtnInput(nullptr), m_onMouseMove(nullptr),
	  m_onKeyboardInput(nullptr) {
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

bool Window::isKeyPressed(KeyboardKey key) const {
	const uint8_t *state = SDL_GetKeyboardState(nullptr);
	uint32_t flags = SDL_GetWindowFlags(m_window);
	return state[key] == 1 && (flags & SDL_WINDOW_INPUT_FOCUS);
}

void Window::onResize(WindowSizeCallback cb) { m_onResize = cb; }

void Window::onMouseButtonInput(MouseButtonCallback cb) {
	m_onMouseBtnInput = cb;
}

void Window::onMouseMove(MouseMoveCallback cb) { m_onMouseMove = cb; }

void Window::onKeyboardInput(KeyboardKeyCallback cb) { m_onKeyboardInput = cb; }

// return 1 to add the event to the event queue, 0 to drop from the event queue
int Window::handleEvent(void *data, SDL_Event *event) {
	Window *wnd = static_cast<Window *>(data);

	double time = static_cast<double>(event->common.timestamp) / 1000;

	switch (event->type) {
		case SDL_WINDOWEVENT: {
			const SDL_WindowEvent &evt = event->window;

			if (evt.windowID == wnd->m_id) {
				switch (evt.event) {
					case SDL_WINDOWEVENT_RESIZED:
						if (wnd->m_onResize) {
							WindowSizeEvent e;
							e.time = time;
							e.width = evt.data1;
							e.width = evt.data2;
							wnd->m_onResize(e);
						}
						break;
				}
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: {
			const SDL_MouseButtonEvent &evt = event->button;
			if (evt.which != SDL_TOUCH_MOUSEID && evt.windowID == wnd->m_id) {
				if (wnd->m_onMouseBtnInput) {
					MouseButtonEvent e;
					e.time = time;
					e.btn = static_cast<MouseButton>(evt.button);
					e.state = static_cast<KeyState>(evt.state);
					e.x = evt.x;
					e.y = evt.y;
					wnd->m_onMouseBtnInput(e);
				}
			}
			break;
		}
		case SDL_MOUSEMOTION: {
			const SDL_MouseMotionEvent &evt = event->motion;
			if (evt.which != SDL_TOUCH_MOUSEID && evt.windowID == wnd->m_id) {
				if (wnd->m_onMouseMove) {
					MouseMoveEvent e;
					e.time = time;
					e.x = evt.x;
					e.y = evt.y;
					wnd->m_onMouseMove(e);
				}
			}
			break;
		}
		case SDL_KEYDOWN:
		case SDL_KEYUP: {
			const SDL_KeyboardEvent &evt = event->key;
			if (evt.windowID == wnd->m_id) {
				if (wnd->m_onKeyboardInput) {
					KeyboardEvent e;
					e.time = time;
					e.key = static_cast<KeyboardKey>(evt.keysym.scancode);
					e.state = static_cast<KeyState>(evt.state);
					e.mods = static_cast<ModifierKey>(evt.keysym.mod);
					e.isRepeat = evt.repeat != 0;

					wnd->m_onKeyboardInput(e);
				}
			}
			break;
		}
	}
	return 1;
}
