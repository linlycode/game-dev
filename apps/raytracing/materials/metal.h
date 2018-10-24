#ifndef METAL_H
#define METAL_H

#include "../random.h"
#include "../material.h"

class Metal : public Material {
public:
	Vector3f albedo;

private:
	RandomNumberGenerator<float> &m_randGen;
	float m_fuzziness;

public:
	Metal(const Vector3f &albedo, float fuzziness)
		: Material(), albedo(albedo),
		  m_randGen(*new RandomNumberGenerator<float>(0, 1)),
		  m_fuzziness(fuzziness < 1 ? fuzziness : 1) {}

	~Metal() { delete &m_randGen; }

	float fuzziness() const { return m_fuzziness; }
	void setFuzziness(float f) { m_fuzziness = f < 1 ? f : 1; }

	bool scatter(const Rayf &ray, const RaycastHit &hit, Vector3f &attenuation,
				 Rayf &scattered) const override;

private:
	Vector3f randomPointInSphere() const;
};

#endif
