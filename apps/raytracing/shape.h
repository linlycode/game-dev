#ifndef SHAPE_H
#define SHAPE_H

#include "math/ray.h"

class Material;

struct RaycastHit {
	float distance;
	Vector3f normal;
	Material *material;

	RaycastHit() : distance(-1), material(nullptr) {}
	RaycastHit(float distance, Vector3f normal, Material &material)
		: distance(distance), normal(normal), material(&material) {}
};

class Shape {
public:
	Material *material;

	Shape() = delete;
	Shape(Material &m) : material(&m) {}

	virtual ~Shape() {}

	// casts the ray to the shape, returns true if the ray hit the
	// shape, and RaycastHit is populated unless it's nullptr
	virtual bool raycast(const Rayf &ray, RaycastHit *hit) const = 0;
};

#endif
