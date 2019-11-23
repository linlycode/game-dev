#include "camera.h"
#include "camera_controller.h"

CameraController::RelativeRotator::RelativeRotator(
	CameraController &ctrlr, const Quaternionf &initRot)
	: m_ctrlr(&ctrlr), m_initRot(initRot) {}

void CameraController::RelativeRotator::setRotation(
	float horizontal, float vertical) {
	float hs = m_ctrlr->m_maxRelRotSpeed.horizontal;
	float vs = m_ctrlr->m_maxRelRotSpeed.vertical;

	Vector3f right = m_initRot.rotate(Vector3f(1, 0, 0));
	Quaternionf rot = Quaternionf::rotate(right, vs * vertical) * m_initRot;

	Vector3f up = rot.rotate(Vector3f(0, 1, 0));

	m_ctrlr->camera->transform.rotation =
		Quaternionf::rotate(up, -hs * horizontal) * rot;
}

CameraController::RelativeRotator CameraController::getRelativeRotator() {
	return RelativeRotator(*this, camera->transform.rotation);
}

CameraController::CameraController(Camera &cam, const Vector3f &maxMoveSpeed,
	const AxesParams &maxRotSpeed, const AxesParams &maxRelRotSpeed)
	: camera(&cam), m_maxMoveSpeed(maxMoveSpeed), m_maxRotSpeed(maxRotSpeed),
	  m_maxRelRotSpeed(maxRelRotSpeed), m_rotSpeed({0, 0}) {}

void CameraController::moveCamera(float x, float y, float z) {
	m_moveSpeed[0] = x;
	m_moveSpeed[1] = y;
	m_moveSpeed[2] = z;
}

void CameraController::rotateCamera(float h, float v) {
	m_rotSpeed.horizontal = m_maxRotSpeed.horizontal * h;
	m_rotSpeed.vertical = m_maxRotSpeed.vertical * v;
}

#define EPSILON 0.000001f

void CameraController::update(double dt) {
	float hs = m_rotSpeed.horizontal;
	float vs = m_rotSpeed.vertical;

	Quaternionf rot = camera->transform.rotation;

	if (std::abs(vs) > EPSILON) {
		Vector3f right = rot.rotate(Vector3f(1, 0, 0));
		rot = Quaternionf::rotate(right, static_cast<float>(-vs * dt)) * rot;
	}

	if (std::abs(hs) > EPSILON) {
		Vector3f up = rot.rotate(Vector3f(0, 1, 0));
		rot = Quaternionf::rotate(up, static_cast<float>(-hs * dt)) * rot;
	}

	camera->transform.rotation = rot;

	camera->transform.translation +=
		rot.rotate(m_maxMoveSpeed.pointwise(m_moveSpeed) * dt);
}
