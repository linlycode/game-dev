#ifndef DIELETRIC_H
#define DIELETRIC_H

#include "../random.h"
#include "../material.h"

class Dielectric : public Material {
	RandomNumberGenerator<float> &m_randGen;

public:
	float refractiveIndex;

	Dielectric(float refractiveIndex)
		: Material(), m_randGen(*new RandomNumberGenerator<float>(0, 1)),
		  refractiveIndex(refractiveIndex) {}

	~Dielectric() { delete &m_randGen; }

	bool scatter(const Rayf &ray, const RaycastHit &hit, Vector3f &attenuation,
				 Rayf &scattered) const override;
};

#endif
