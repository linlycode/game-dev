#include <stdexcept>

#include <fmt/printf.h>

#include "gl_err.h"
#include "shader_util.h"

CreateShaderError::CreateShaderError(GLenum type)
	: GLError(glGetError(),
		  fmt::sprintf("create %s failed", get_shader_type_name(type))),
	  type(type) {}

CompileShaderError::CompileShaderError(
	GLenum type, GLuint shader, std::string log)
	: GLError(glGetError(), fmt::sprintf("compile %s %d failed, log:\n%s",
								get_shader_type_name(type), shader, log)),
	  type(type), shader(shader), log(log) {}

CreateProgramError::CreateProgramError(const std::vector<GLuint> &shaders)
	: GLError(glGetError(), "create program failed"), shaders(shaders) {}

LinkProgramError::LinkProgramError(GLuint program, std::string log)
	: GLError(glGetError(), fmt::sprintf("link program %d failed", program)),
	  program(program), log(log) {}

std::string get_shader_type_name(GLenum type) {
	switch (type) {
	case GL_VERTEX_SHADER:
		return "vertex shader";
	case GL_TESS_CONTROL_SHADER:
		return "tessellation control shader";
	case GL_TESS_EVALUATION_SHADER:
		return "tessellation evaluation shader";
	case GL_GEOMETRY_SHADER:
		return "geometry shader";
	case GL_FRAGMENT_SHADER:
		return "fragment shader";
	case GL_COMPUTE_SHADER:
		return "compute shader";
	default:
		return fmt::sprintf("unknown shader(%d)", type);
	}
}

std::string get_shader_log(GLuint shader) {
	GLint len;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len); // len includes '\0'
	if (len == 0) {
		return "";
	}

	std::string log(len, ' ');
	GLsizei logLen;
	// logLen doesn't include '\0'
	glGetShaderInfoLog(shader, log.size(), &logLen, &log[0]);
	log.resize(logLen);
	return log;
}

GLuint create_shader(GLenum type, const std::vector<std::string> &sources) {
	GLuint shader = glCreateShader(type);
	if (!shader) {
		throw CreateShaderError(type);
	}

	std::vector<const char *> srcs(sources.size());
	for (size_t i = 0; i < sources.size(); i++) {
		srcs[i] = sources[i].c_str();
	}
	glShaderSource(shader, srcs.size(), srcs.data(), nullptr);

	glCompileShader(shader);

	GLint ok;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		throw CompileShaderError(type, shader, get_shader_log(shader));
	}
	return shader;
}

std::string get_program_log(GLuint program) {
	GLint len;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

	std::string log(len, ' ');
	GLsizei logLen;
	glGetProgramInfoLog(program, log.size(), &logLen, &log[0]);
	log.resize(logLen);
	return log;
}

GLuint create_program(const std::vector<GLuint> &shaders) {
	GLuint program = glCreateProgram();
	if (!program) {
		throw CreateProgramError(shaders);
	}

	for (size_t i = 0; i < shaders.size(); i++) {
		glAttachShader(program, shaders[i]);
	}

	glLinkProgram(program);

	GLint ok;
	glGetProgramiv(program, GL_LINK_STATUS, &ok);
	if (!ok) {
		throw LinkProgramError(program, get_program_log(program));
	}
	return program;
}
