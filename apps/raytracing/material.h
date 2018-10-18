#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/ray.h"

class RaycastHit;

class Material {
public:
	virtual ~Material() {}

	virtual bool scatter(const Rayf &ray, const RaycastHit &hit,
						 Vector3f &attenuation, Rayf &scattered) const = 0;
};

#endif
