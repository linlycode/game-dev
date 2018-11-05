#include <iostream>
#include <stdexcept>

#include "shader_util.h"
#include "glfw_app.h"

namespace {
	void resize_viewport(GLFWwindow *window, int width, int height);
	GLuint make_program();
	GLuint make_vertex_array(GLuint program);
} // namespace

int main() {
	try {
		GLFWApp app;
		GLFWwindow *window =
			app.createWindow(800, 600, "OpenGL App", nullptr, nullptr);

		glfwSetFramebufferSizeCallback(window, resize_viewport);

		glfwMakeContextCurrent(window);

		load_GL_funcs();

		GLuint program = make_program();
		glUseProgram(program);

		GLuint vertArray = make_vertex_array(program);
		glBindVertexArray(vertArray);

		glClearColor(0.2f, 0.3f, 0.3f, 1);

		while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

namespace {

	void resize_viewport(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	GLuint make_program() {
		// clang-format off
		GLuint vertShader = create_shader(GL_VERTEX_SHADER, {
			"#version 450\n"
			"in vec3 pos;\n"
			"void main() {\n"
			"\tgl_Position = vec4(pos, 1);\n"
			"}\n"});

		GLuint fragShader = create_shader(GL_FRAGMENT_SHADER, {
			"#version 450\n"
			"out vec4 color;\n"
			"void main() {\n"
			"\tcolor=vec4(1, 0.5, 0.2, 1);\n"
			"}\n"});
		// clang-format on
		return create_program({vertShader, fragShader});
	}

	GLuint make_vertex_array(GLuint program) {
		// clang-format off
		float vertices[] = {
			-0.5f, -0.5f, 0,
			0.5f,  -0.5f, 0,
			0,     0.5f,  0
		};
		// clang-format on

		GLuint buf;
		glGenBuffers(1, &buf);
		glBindBuffer(GL_ARRAY_BUFFER, buf);
		glBufferData(
			GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint vertArray;
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);

		GLint pos = glGetAttribLocation(program, "pos");
		glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,
			reinterpret_cast<const void *>(0));
		glEnableVertexArrayAttrib(vertArray, pos);
		return vertArray;
	}

} // namespace
