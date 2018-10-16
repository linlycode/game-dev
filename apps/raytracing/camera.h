#ifndef CAMERA_H
#define CAMERA_H

#include "math/ray.h"

struct Camera {
	Vector3f origin, lowerLeft, horizontal, vertical;

	Camera()
		: lowerLeft(-2, -1.125f, -1), horizontal(4, 0, 0),
		  vertical(0, 2.25f, 0) {}

	Rayf genRay(float u, float v) const {
		Vector3f direction = lowerLeft + u * horizontal + v * vertical - origin;
		return Rayf(origin, direction);
	}
};

#endif
