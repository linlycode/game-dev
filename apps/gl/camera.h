#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"

class Camera {
public:
	Transformf transform;
	Matrix4f projection;

public:
	Camera(const Transformf &transform, const Matrix4f &proj);

	Matrix4f getViewMatrix() const;
};

#endif
