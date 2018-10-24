#ifndef OPTICS_H
#define OPTICS_H

#include "math/vector.h"

Vector3f reflect(const Vector3f &v, const Vector3f &n);

bool refract(const Vector3f &v, const Vector3f &n, float r,
			 Vector3f &refracted);

#endif
