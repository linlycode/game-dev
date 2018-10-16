#ifndef SPHERE_H
#define SPHERE_H

#include "math/vector.h"
#include "shape.h"

class Sphere : public Shape {
public:
	Vector3f center;
	float radius;

public:
	Sphere(Vector3f center, float radius)
		: Shape(), center(center), radius(radius) {}

	bool raycast(const Rayf &ray, RaycastHit *hit) const override;

private:
	void fillRaycastHit(const Rayf &ray, float distance, RaycastHit *hit) const;
};

#endif
