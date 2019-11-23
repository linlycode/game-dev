#include "mouse_input.h"
#include "window.h"
#include "mouse_input_handler.h"

using namespace std::placeholders;

MouseInputHandler::MouseInputHandler(Window &window, CameraController &camCtl)
	: m_window(&window), m_camCtl(&camCtl), m_shouldRotate(false) {

	m_window->onMouseButtonInput(
		std::bind(&MouseInputHandler::onMouseButtonInput, this, _1));

	m_window->onMouseMove(std::bind(&MouseInputHandler::onMouseMove, this, _1));
}

void MouseInputHandler::onMouseButtonInput(MouseButtonEvent e) {
	if (e.btn == MOUSE_BUTTON_LEFT) {
		if (e.state == PRESSED) {
			m_rotAnchor = {e.x, e.y};
			m_relRot = m_camCtl->getRelativeRotator();
			m_shouldRotate = true;
		} else {
			m_shouldRotate = false;
		}
	}
}

void MouseInputHandler::onMouseMove(MouseMoveEvent e) {
	if (m_shouldRotate) {
		int width, height;
		m_window->getSize(width, height);

		float horizontal = 2 * static_cast<float>(e.x - m_rotAnchor[0]) / width;
		float vertical = -2 * static_cast<float>(e.y - m_rotAnchor[1]) / height;

		m_relRot.setRotation(horizontal, vertical);
	}
}
