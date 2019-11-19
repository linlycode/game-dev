#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "infra/fmt.h"
#include "gl_loader.h"

void load_GL_funcs() {
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		throw std::runtime_error(
			fmt::sprintf("failed to load OpenGL functions, version: %d.%d",
				GLVersion.major, GLVersion.minor));
	}
}
