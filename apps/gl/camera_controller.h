#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "math/constants.h"
#include "transform.h"

class Camera;

class CameraController {
public:
	Camera *camera;

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

	struct AxesParams {
		float horizontal;
		float vertical;
	};

private:
	Vector3f m_maxMoveSpeed;
	AxesParams m_maxRotSpeed;
	AxesParams m_maxRelRotSpeed;
	AxesParams m_rotSpeed;
	Vector3f m_moveSpeed;

public:
	CameraController(Camera &cam,
		const Vector3f &maxMoveSpeed = Vector3f(2, 2, 2),
		const AxesParams &maxRotSpeed = {float(M_PI / 2), float(M_PI / 2)},
		const AxesParams &maxRelRotSpeed = {float(M_PI / 2), float(M_PI / 2)});

	RelativeRotator getRelativeRotator();

	void moveCamera(float x, float y, float z);

	void rotateCamera(float horizontal, float vertical);

	void update(double dt); // in seconds
};

#endif
