#include "../shape.h"
#include "lambertian.h"

bool Lambertian::scatter(const Rayf &ray, const RaycastHit &hit,
						 Vector3f &attenuation, Rayf &scattered) const {
	Vector3f hitPoint = ray.point(hit.distance);
	Vector3f direction = hit.normal + randomPointInSphere();
	scattered = Rayf(hitPoint, direction);
	attenuation = this->albedo;
	return true;
}

Vector3f Lambertian::randomPointInSphere() const {
	Vector3f p;
	do {
		p = 2.0f * Vector3f(m_randGen(), m_randGen(), m_randGen()) -
			Vector3f(1, 1, 1);
	} while (p * p >= 1);
	return p;
}
