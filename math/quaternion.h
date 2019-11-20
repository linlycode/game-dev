#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "vector.h"

template <typename T>
class Quaternion {
	Vector<T, 3> m_image;
	T m_real;

public:
	static Quaternion identity() { return Quaternion({0, 0, 0}, 1); }

	static Quaternion rotate(const Vector<T, 3> &axis, T radian) {
		T halfAngle = radian / 2;
		return Quaternion<T>(
			std::sin(halfAngle) * axis.normalized(), std::cos(halfAngle));
	}

	Quaternion() : m_real(0) {}

	Quaternion(Vector<T, 3> image, T real) : m_image(image), m_real(real) {}

	const Vector<T, 3> &image() const { return m_image; }

	T real() const { return m_real; }

	Quaternion conjugate() const { return Quaternion(-m_image, m_real); }

	T norm() const { return std::sqrt(m_image.dot(m_image) + m_real * m_real); }

	// versor is unit quaternion
	Quaternion versor() const { return *this / norm(); }

	Quaternion operator+(const Quaternion &other) const {
		return Quaternion(m_image + other.m_image, m_real + other.m_real);
	}

	Quaternion operator-(const Quaternion &other) const {
		return Quaternion(m_image - other.m_image, m_real - other.m_real);
	}

	Quaternion operator*(T s) const {
		return Quaternion(m_image * s, m_real * s);
	}

	Quaternion operator/(T s) const {
		return Quaternion(m_image / s, m_real / s);
	}

	Quaternion operator*(const Quaternion &other) const {
		const Vector<T, 3> &u = m_image, &v = other.m_image;
		T s = m_real, t = other.m_real;
		return Quaternion(u.cross(v) + t * u + s * v, s * t - u.dot(v));
	}

	Quaternion inversed() const {
		T n = this->norm();
		return this->conjugate() / (n * n);
	}

	Vector<T, 3> rotate(const Vector<T, 3> &vec) const {
		Quaternion p(Vector<T, 3>(vec[0], vec[1], vec[2]), 0);
		Quaternion v = versor();
		Quaternion q = v * p * v.conjugate();
		return q.m_image;
	}
};

template <typename T>
Quaternion<T> operator*(T s, const Quaternion<T> &q) {
	return q * s;
}

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

#endif
