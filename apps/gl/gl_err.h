#ifndef GL_ERR_H
#define GL_ERR_H

#include <string>
#include <stdexcept>

#include "gl_loader.h"

struct GLError : public std::exception {
	GLenum err;
	std::string detail;

	GLError(GLenum err, std::string detail)
		: std::exception(), err(err), detail(detail) {}

	const char *what() const noexcept override { return detail.c_str(); }
};

std::string get_GL_error_name(GLenum err);

#endif
