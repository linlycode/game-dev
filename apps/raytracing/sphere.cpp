#include "sphere.h"

void Sphere::fillRaycastHit(const Rayf &ray, float distance,
							RaycastHit *hit) const {
	if (hit) {
		Vector3f normal = (ray.point(distance) - this->center).normalized();
		*hit = RaycastHit(distance, normal, *this->material);
	}
}

bool Sphere::raycast(const Rayf &ray, RaycastHit *hit) const {
	Vector3f co = ray.origin() - this->center;
	float a = ray.direction().dot(ray.direction());
	float b = 2.0f * co.dot(ray.direction());
	float c = co.dot(co) - this->radius * this->radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return false;
	}

	float d = (-b - std::sqrt(discriminant)) / (2 * a);
	if (d > 0.001f) { // ignore near-zero length rays to avoid shadow acne
		fillRaycastHit(ray, d, hit);
		return true;
	}

	d = (-b + std::sqrt(discriminant)) / (2 * a);
	if (d > 0.001f) {
		fillRaycastHit(ray, d, hit);
		return true;
	}
	return false;
}
