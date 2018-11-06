#include <iostream>
#include <stdexcept>

#include <fmt/printf.h>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

#include "infra/filepath.h"

#include "shader_util.h"
#include "glfw_app.h"

namespace {
	void resize_viewport(GLFWwindow *window, int width, int height);
	GLuint make_program();
	GLuint make_texture(const std::string &filename);
	GLuint make_vertex_array(GLuint program);
} // namespace

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		std::cerr << "Please specify asset directory" << std::endl;
		return -1;
	}

	std::string assetDir(argv[1]);

	try {
		GLFWApp app;
		GLFWwindow *window =
			app.createWindow(800, 600, "OpenGL App", nullptr, nullptr);

		glfwSetFramebufferSizeCallback(window, resize_viewport);

		glfwMakeContextCurrent(window);

		load_GL_funcs();

		GLuint program = make_program();
		glUseProgram(program);

		GLuint texture =
			make_texture(filepath::join(assetDir, "wooden container.jpg"));
		glBindTexture(GL_TEXTURE_2D, texture);

		GLuint vertArray = make_vertex_array(program);
		glBindVertexArray(vertArray);

		glClearColor(0.2f, 0.3f, 0.3f, 1);

		while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
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
			"in vec3 aPos;\n"
			"in vec2 aTexCoord;\n"
			"out vec2 texCoord;\n"
			"void main() {\n"
			"\tgl_Position = vec4(aPos, 1);\n"
			"\ttexCoord = aTexCoord;\n"
			"}\n"});

		GLuint fragShader = create_shader(GL_FRAGMENT_SHADER, {
			"#version 450\n"
			"in vec2 texCoord;\n"
			"out vec4 color;\n"
			"uniform sampler2D uTexture;\n"
			"void main() {\n"
			"\tcolor = texture(uTexture, texCoord);\n"
			"}\n"});
		// clang-format on
		return create_program({vertShader, fragShader});
	}

	GLuint make_texture(const std::string &filename) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nChan;
		unsigned char *imgData =
			stbi_load(filename.c_str(), &width, &height, &nChan, 0);
		if (!imgData) {
			throw std::runtime_error(
				fmt::sprintf("failed to open file \"%s\"", filename));
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imgData);
		return texture;
	}

	GLuint make_vertex_array(GLuint program) {
		// clang-format off
		float vertices[] = {
			// positions         // texture coordinates
			-0.5f, -0.5f, 0,     0, 0,
			 0.5f, -0.5f, 0,     1, 0,
			-0.5f,  0.5f, 0,     0, 1,
			 0.5f,  0.5f, 0,     1, 1
		};

		unsigned int indices[] = {
			0, 1, 2, 3
		};
		// clang-format on

		GLuint vertArray;
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);

		GLuint vertBuf;
		glGenBuffers(1, &vertBuf);
		glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
		glBufferData(
			GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint indexBuf;
		glGenBuffers(1, &indexBuf);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLsizei stride = sizeof(float) * 5;

		GLint pos = glGetAttribLocation(program, "aPos");
		glEnableVertexArrayAttrib(vertArray, pos);
		glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, stride,
			reinterpret_cast<const void *>(0));

		GLint texCoord = glGetAttribLocation(program, "aTexCoord");
		glEnableVertexArrayAttrib(vertArray, texCoord);
		glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, stride,
			reinterpret_cast<const void *>(sizeof(float) * 3));
		return vertArray;
	}

} // namespace
