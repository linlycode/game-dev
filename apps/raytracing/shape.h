#ifndef SHAPE_H
#define SHAPE_H

#include "math/ray.h"

struct RaycastHit {
	float distance;
	Vector3f normal;

	RaycastHit() : distance(-1) {}
	RaycastHit(float distance, Vector3f normal)
		: distance(distance), normal(normal) {}
};

class Shape {
public:
	virtual ~Shape() {}

	// casts the ray to the shape, returns true if the ray hit the
	// shape, and RaycastHit is populated unless it's nullptr
	virtual bool raycast(const Rayf &ray, RaycastHit *hit) const = 0;
};

#endif
