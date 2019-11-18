#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>

#include "infra/fmt.h"
#include "Window.h"
#include "app.h"

App::App() : m_initialized(false), m_shouldExit(false) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		m_shouldExit = true;

		throw std::runtime_error(
			fmt::sprintf("SDL initialization failed, %s", SDL_GetError()));
	}

	m_initialized = true;
}

App::~App() {
	if (m_initialized) {
		SDL_Quit();
	}
}

void App::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_shouldExit = true;
			break;
		}
	}
}

bool App::shouldExit() { return m_shouldExit; }
