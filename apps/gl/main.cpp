#include <iostream>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

#include "infra/fmt.h"
#include "infra/filepath.h"

#include "shader_util.h"
#include "glfw_app.h"

namespace {
	void resize_viewport(GLFWwindow *window, int width, int height);
	GLuint make_program();
	GLuint make_texture(
		GLenum texUnit, const std::string &filename, bool vflip = true);
	void bind_texture(GLuint program, const char *uniform, GLint index);
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

		GLuint texture0 = make_texture(
			GL_TEXTURE0, filepath::join(assetDir, "wooden container.jpg"));
		glBindTexture(GL_TEXTURE_2D, texture0);
		bind_texture(program, "uTexture0", 0);

		GLuint texture1 = make_texture(
			GL_TEXTURE1, filepath::join(assetDir, "awesomeface.png"));
		glBindTexture(GL_TEXTURE_2D, texture1);
		bind_texture(program, "uTexture1", 1);

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
			"uniform sampler2D uTexture0;\n"
			"uniform sampler2D uTexture1;\n"
			"void main() {\n"
			"\tcolor = mix(texture(uTexture0, texCoord), texture(uTexture1, texCoord), 0.2);\n"
			"}\n"});
		// clang-format on
		return create_program({vertShader, fragShader});
	}

	GLuint make_texture(
		GLenum texUnit, const std::string &filename, bool vflip) {
		glActiveTexture(texUnit);

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(vflip);

		int width, height, nChan;
		unsigned char *imgData =
			stbi_load(filename.c_str(), &width, &height, &nChan, 0);
		if (!imgData) {
			throw std::runtime_error(
				fmt::sprintf("failed to open file \"%s\"", filename.c_str()));
		}

		GLenum format = nChan == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
			GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imgData);
		return texture;
	}

	void bind_texture(GLuint program, const char *uniform, GLint index) {
		GLint loc = glGetUniformLocation(program, uniform);
		glUniform1i(loc, index);
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