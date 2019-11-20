#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "math/constants.h"
#include "transform.h"

class Camera;

class CameraController {
public:
	// RelativeRotator rotates the camera relative to an initial orientation
	class RelativeRotator {
		CameraController *m_ctrlr;
		Quaternionf m_initRot;

		RelativeRotator(CameraController &ctrlr, const Quaternionf &initRot);

		friend class CameraController;

	public:
		RelativeRotator() : m_ctrlr(nullptr) {}

		// horizontal and vertical values are between -1.0 and 1.0
		void setRotation(float horizontal, float vertical);
	};

	friend class RelativeRotator;

	struct RotateSpeed {
		float horizontal;
		float vertical;
	};

private:
	Camera *m_camera;
	RotateSpeed m_rotSpeed;
	RotateSpeed m_relRotSpeed;

public:
	CameraController(Camera &cam,
		const RotateSpeed &rotSpeed = {static_cast<float>(M_PI / 6),
			static_cast<float>(M_PI / 9)},
		const RotateSpeed &relRotSpeed = {static_cast<float>(M_PI / 2),
			static_cast<float>(M_PI / 2)})
		: m_camera(&cam), m_rotSpeed(rotSpeed), m_relRotSpeed(relRotSpeed) {}

	RelativeRotator getRelativeRotator();

	void rotateCamera(float horizontal, float vertical);
};

#endif
