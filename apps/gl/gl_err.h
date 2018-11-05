#ifndef GL_ERR_H
#define GL_ERR_H

#include <stdexcept>

#include "gl_loader.h"

struct GLError : public std::exception {
	GLenum err;
	std::string detail;

	GLError(GLenum err, std::string detail)
		: std::exception(), err(err), detail(detail) {}

	const char *what() const noexcept override { return detail.c_str(); }
};

#endif
