#ifndef RAY_H
#define RAY_H

#include "vector.h"

template <typename T>
class Ray {
private:
	Vector<T, 3> m_origin, m_direction;

public:
	Ray() {}

	Ray(Vector<T, 3> origin, Vector<T, 3> direction)
		: m_origin(origin), m_direction(direction.normalized()) {}

	const Vector<T, 3> &origin() const { return m_origin; }
	Vector<T, 3> &origin() { return m_origin; }

	const Vector<T, 3> &direction() const { return m_direction; }

	void setDirection(const Vector<T, 3> &direction) {
		m_direction = direction.normalized();
	}

	Vector<T, 3> point(T k) const { return m_origin + k * m_direction; }
};

typedef Ray<float> Rayf;
typedef Ray<double> Rayd;

#endif
