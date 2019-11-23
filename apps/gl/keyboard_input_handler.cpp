#include "window.h"
#include "camera_controller.h"
#include "keyboard_input_handler.h"

KeyboardInputHandler::KeyboardInputHandler(
	Window &window, CameraController &camCtl)
	: m_window(&window), m_camCtl(&camCtl) {}

void KeyboardInputHandler::handleInput() {
	float h = 0;

	if (m_window->isKeyPressed(KEY_Q)) {
		h -= 1;
	}
	if (m_window->isKeyPressed(KEY_E)) {
		h += 1;
	}

	m_camCtl->rotateCamera(h, 0);

	float x = 0, y = 0, z = 0;

	if (m_window->isKeyPressed(KEY_A)) {
		x -= 1;
	}
	if (m_window->isKeyPressed(KEY_D)) {
		x += 1;
	}
	if (m_window->isKeyPressed(KEY_W)) {
		z -= 1;
	}
	if (m_window->isKeyPressed(KEY_S)) {
		z += 1;
	}
	if (m_window->isKeyPressed(KEY_Z)) {
		y -= 1;
	}
	if (m_window->isKeyPressed(KEY_X)) {
		y += 1;
	}

	m_camCtl->moveCamera(x, y, z);
}
