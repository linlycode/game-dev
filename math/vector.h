#ifndef VECTOR_H
#define VECTOR_H

#include "vec_base.h"

template <typename T, size_t N>
class Vector : public VectorBase<T, N, Vector> {
	VECTOR_CTORS(Vector, T, N)
};

template <typename T>
class Vector<T, 3> : public VectorBase<T, 3, Vector> {
	VECTOR_CTORS(Vector, T, 3)

public:
	Vector(T x, T y, T z) : Vector({x, y, z}) {}

	Vector cross(const Vector &other) const {
		T u = (*this)[0], v = (*this)[1], w = (*this)[2];
		T x = other[0], y = other[1], z = other[2];
		return Vector({v * z - w * y, w * x - u * z, u * y - v * x});
	}
};

template <typename T, size_t N>
Vector<T, N> operator*(T s, const Vector<T, N> &v) {
	return v * s;
}

typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;

typedef Vector<double, 2> Vector2d;
typedef Vector<double, 3> Vector3d;
typedef Vector<double, 4> Vector4d;

#endif
