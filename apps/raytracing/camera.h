#ifndef CAMERA_H
#define CAMERA_H

#include "math/ray.h"

class Camera {
public:
	Camera(const Vector3f &lookFrom, const Vector3f &lookAt, const Vector3f &up,
		   float vFov, float aspect);

	Rayf genRay(float u, float v) const;

private:
	Vector3f m_origin, m_lowerLeft, m_horizontal, m_vertical;
};

#endif
