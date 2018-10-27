#include "camera.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera::Camera(const Vector3f &lookFrom, const Vector3f &lookAt,
			   const Vector3f &up, float vFov, float aspect) {
	float theta = vFov * M_PI / 180;
	float halfHeight = std::tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	Vector3f w = (lookFrom - lookAt).normalized();
	Vector3f u = up.cross(w).normalized();
	Vector3f v = w.cross(u);

	m_origin = lookFrom;
	m_lowerLeft = m_origin - halfWidth * u - halfHeight * v - w;
	m_horizontal = 2 * halfWidth * u;
	m_vertical = 2 * halfHeight * v;
}

Rayf Camera::genRay(float u, float v) const {
	Vector3f direction =
		m_lowerLeft + u * m_horizontal + v * m_vertical - m_origin;
	return Rayf(m_origin, direction);
}
