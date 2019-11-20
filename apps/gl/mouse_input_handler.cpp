#include "mouse_input.h"
#include "window.h"
#include "mouse_input_handler.h"

void MouseInputHandler::onMouseDown(enum MouseButton btn, int x, int y) {
	if (btn == MOUSE_BUTTON_LEFT) {
		m_rotAnchor = {x, y};
		m_relRot = m_camCtl->getRelativeRotator();
		m_shouldRotate = true;
	}
}

void MouseInputHandler::onMouseUp(enum MouseButton btn, int, int) {
	if (btn == MOUSE_BUTTON_LEFT) {
		m_shouldRotate = false;
	}
}

void MouseInputHandler::onMouseMove(int x, int y) {
	if (m_shouldRotate) {
		int width, height;
		m_window->getSize(width, height);

		float horizontal = 2 * static_cast<float>(x - m_rotAnchor[0]) / width;
		float vertical = -2 * static_cast<float>(y - m_rotAnchor[1]) / height;

		m_relRot.setRotation(horizontal, vertical);
	}
}
