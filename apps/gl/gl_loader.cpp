#include <string>
#include <stdexcept>

#include <fmt/printf.h>

#include "gl_loader.h"

void load_GL_funcs() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::string msg = fmt::sprintf("GLEW initialization failed, %s",
			reinterpret_cast<const char *>(glewGetErrorString(err)));
		throw std::runtime_error(msg);
	}
}
