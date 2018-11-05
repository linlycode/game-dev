#ifndef GLFW_APP_H
#define GLFW_APP_H

#include <vector>

#include <GLFW/glfw3.h>

class GLFWApp {
public:
	GLFWApp();
	GLFWApp(const GLFWApp &) = delete;
	~GLFWApp();

	GLFWwindow *createWindow(int width, int height, const char *title,
		GLFWmonitor *monitor, GLFWwindow *share);

	void destroyWindow(GLFWwindow *);

private:
	bool m_initialized;
	std::vector<GLFWwindow *> m_windows;
};

#endif
