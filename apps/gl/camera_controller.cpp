#include "camera.h"
#include "camera_controller.h"

CameraController::RelativeRotator::RelativeRotator(
	CameraController &ctrlr, const Quaternionf &initRot)
	: m_ctrlr(&ctrlr), m_initRot(initRot) {}

void CameraController::RelativeRotator::setRotation(
	float horizontal, float vertical) {
	float hs = m_ctrlr->m_relRotSpeed.horizontal;
	float vs = m_ctrlr->m_relRotSpeed.vertical;

	Vector3f right = m_initRot.rotate(Vector3f(1, 0, 0));
	Quaternionf rot = Quaternionf::rotate(right, vs * vertical) * m_initRot;

	Vector3f up = rot.rotate(Vector3f(0, 1, 0));

	m_ctrlr->m_camera->transform.rotation =
		Quaternionf::rotate(up, -hs * horizontal) * rot;
}

CameraController::RelativeRotator CameraController::getRelativeRotator() {
	return RelativeRotator(*this, m_camera->transform.rotation);
}

void CameraController::rotateCamera(float horizontal, float vertical) {
	float hs = m_rotSpeed.horizontal;
	float vs = m_rotSpeed.vertical;

	Vector3f right = m_camera->transform.rotation.rotate(Vector3f(1, 0, 0));
	Quaternionf rot = Quaternionf::rotate(right, -vs * vertical) *
					  m_camera->transform.rotation;

	Vector3f up = rot.rotate(Vector3f(0, 1, 0));
	m_camera->transform.rotation =
		Quaternionf::rotate(up, -hs * horizontal) * rot;
}
