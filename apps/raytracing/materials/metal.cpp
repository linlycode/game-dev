#include "../shape.h"
#include "../optics.h"
#include "metal.h"

bool Metal::scatter(const Rayf &ray, const RaycastHit &hit,
					Vector3f &attenuation, Rayf &scattered) const {
	Vector3f hitPoint = ray.point(hit.distance);
	Vector3f direction = reflect(ray.direction(), hit.normal) +
						 m_fuzziness * randomPointInSphere();
	scattered = Rayf(hitPoint, direction);
	attenuation = this->albedo;
	return scattered.direction().dot(hit.normal) > 0;
}

Vector3f Metal::randomPointInSphere() const {
	Vector3f p;
	do {
		p = 2.0f * Vector3f(m_randGen(), m_randGen(), m_randGen()) -
			Vector3f(1, 1, 1);
	} while (p * p >= 1);
	return p;
}
