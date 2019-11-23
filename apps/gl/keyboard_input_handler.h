#ifndef KEYBOARD_INPUT_HANDLER_H
#define KEYBOARD_INPUT_HANDLER_H

class Window;
class CameraController;

class KeyboardInputHandler {
	Window *m_window;
	CameraController *m_camCtl;

public:
	KeyboardInputHandler(Window &window, CameraController &camCtl);

	void handleInput();
};

#endif
