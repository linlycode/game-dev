#include <stdexcept>
#include <iostream>

#include "infra/fmt.h"
#include "glfw_app.h"

static void log_error(int code, const char *description) {
	fmt::fprintf(std::cerr, "GLFW error: #%d %s\n", code, description);
}

GLFWApp::GLFWApp() : m_initialized(false) {
	if (!glfwInit()) {
		throw std::runtime_error("GLFW initialization failed");
	}
	glfwSetErrorCallback(log_error);
	m_initialized = true;
}

GLFWApp::~GLFWApp() {
	for (GLFWwindow *w : m_windows) {
		glfwDestroyWindow(w);
	}

	if (m_initialized) {
		glfwTerminate();
	}
}

GLFWwindow *GLFWApp::createWindow(int width, int height, const char *title,
	GLFWmonitor *monitor, GLFWwindow *share) {
	GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window) {
		throw std::runtime_error("failed to create GLFW window");
	}
	m_windows.push_back(window);
	return window;
}

void GLFWApp::destroyWindow(GLFWwindow *window) {
	for (auto w = m_windows.begin(); w != m_windows.end(); w++) {
		if (*w == window) {
			glfwDestroyWindow(*w);
			m_windows.erase(w);
			break;
		}
	}
}
