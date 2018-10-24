#include "optics.h"

Vector3f reflect(const Vector3f &v, const Vector3f &n) {
	return v - 2 * v.dot(n) * n;
}

bool refract(const Vector3f &v, const Vector3f &n, float r,
			 Vector3f &refracted) {
	float dt = v * n;
	float discriminant = 1 - r * r * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = r * (v - dt * n) - n * std::sqrt(discriminant);
		return true;
	}
	return false;
}
