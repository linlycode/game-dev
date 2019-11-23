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
}
