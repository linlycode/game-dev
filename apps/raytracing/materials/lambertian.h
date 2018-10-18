#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../random.h"
#include "../material.h"

class Lambertian : public Material {
	RandomNumberGenerator<float> &m_randGen;

public:
	Vector3f albedo;

	Lambertian(const Vector3f &albedo)
		: Material(), m_randGen(*new RandomNumberGenerator<float>(0, 1)),
		  albedo(albedo) {}

	~Lambertian() { delete &m_randGen; }

	virtual bool scatter(const Rayf &ray, const RaycastHit &hit,
						 Vector3f &attenuation, Rayf &scattered) const;

private:
	Vector3f randomPointInSphere() const;
};

#endif
