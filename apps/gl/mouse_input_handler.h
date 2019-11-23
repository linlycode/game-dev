#ifndef MOUSE_INPUT_HANDLER_H
#define MOUSE_INPUT_HANDLER_H

#include "camera_controller.h"

class Window;

class MouseInputHandler {
	Window *m_window;
	CameraController *m_camCtl;
	bool m_shouldRotate;
	CameraController::RelativeRotator m_relRot;
	Vector<int, 2> m_rotAnchor;

public:
	MouseInputHandler(Window &window, CameraController &camCtl);

	void onMouseButtonInput(MouseButtonEvent);

	void onMouseMove(MouseMoveEvent);
};

#endif
