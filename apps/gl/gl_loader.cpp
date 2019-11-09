#include <string>
#include <stdexcept>

#include <fmt/printf.h>

#include "gl_loader.h"

void load_GL_funcs() {
	if (!gladLoadGL()) {
		throw std::runtime_error(
			fmt::sprintf("failed to load OpenGL functions, version: %d.%d",
				GLVersion.major, GLVersion.minor));
	}
}
