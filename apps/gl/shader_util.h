#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <string>
#include <vector>

#include "gl_err.h"

struct CreateShaderError : public GLError {
	GLenum type;

	CreateShaderError(GLenum type);
};

struct CompileShaderError : public GLError {
	GLenum type;
	GLuint shader;
	std::string log;

	CompileShaderError(GLenum type, GLuint shader, std::string log);
};

struct CreateProgramError : public GLError {
	std::vector<GLuint> shaders;

	CreateProgramError(const std::vector<GLuint> &shaders);
};

struct LinkProgramError : public GLError {
	GLuint program;
	std::string log;

	LinkProgramError(GLuint program, std::string log);
};

std::string get_shader_type_name(GLenum type);

std::string get_shader_log(GLuint shader);

// create_shader creates a shader and compiles it, returns the shader name if
// successful, otherwise throws CreateShaderError or CompileShaderError
GLuint create_shader(GLenum type, const std::vector<std::string> &sources);

std::string get_program_log(GLuint program);

// create_program creates a program and link it, returns the program name if
// successful, otherwise throws CreateProgramError or LinkProgramError
GLuint create_program(const std::vector<GLuint> &shaders);

#endif
