#include "camera.h"

Camera::Camera(const Transformf &transform, const Matrix4f &proj)
	: transform(transform), projection(proj) {}

Matrix4f Camera::getViewMatrix() const {
	return quaternion_to_matrix(transform.rotation.conjugate()) *
		   tfm::translate(-transform.translation);
}
