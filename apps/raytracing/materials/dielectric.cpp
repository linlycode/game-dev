#include "../shape.h"
#include "../optics.h"
#include "dielectric.h"

static float schlick(float cosine, float refractiveIndex) {
	float r = (1 - refractiveIndex) / (1 + refractiveIndex);
	r *= r;
	return r + (1 - r) * std::pow(1 - cosine, 5);
}

bool Dielectric::scatter(const Rayf &ray, const RaycastHit &hit,
						 Vector3f &attenuation, Rayf &scattered) const {
	Vector3f normal;
	float r, cosine;
	if (ray.direction() * hit.normal > 0) {
		normal = -hit.normal;
		r = this->refractiveIndex;
		cosine = this->refractiveIndex * ray.direction().dot(hit.normal) /
				 ray.direction().magnitude();
	} else {
		normal = hit.normal;
		r = 1.0f / this->refractiveIndex;
		cosine = -ray.direction().dot(hit.normal) / ray.direction().magnitude();
	}

	attenuation = Vector3f(1.0f, 1.0f, 1.0f);

	Vector3f refractDirection;
	float reflectProb;
	if (refract(ray.direction(), normal, r, refractDirection)) {
		reflectProb = schlick(cosine, this->refractiveIndex);
	} else {
		reflectProb = 1;
	}

	Vector3f hitPoint = ray.point(hit.distance);
	if (m_randGen() < reflectProb) {
		scattered = Rayf(hitPoint, reflect(ray.direction(), hit.normal));
	} else {
		scattered = Rayf(hitPoint, refractDirection);
	}
	return true;
}
