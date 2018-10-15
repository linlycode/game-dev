#ifndef VEC_BASE_H
#define VEC_BASE_H

#include <cmath>
#include <algorithm>

template <typename T, size_t N, template <typename, size_t> class Derived>
class VectorBase {
private:
	typedef Derived<T, N> Vec;

private:
	T m_data[N];

protected:
	VectorBase(const char *) {} // no init

public:
	VectorBase() { std::fill(m_data, m_data + N, 0); }

	template <typename U>
	VectorBase(const U (&a)[N]) {
		std::copy(a, a + N, m_data);
	}

	template <typename U>
	VectorBase(const Derived<U, N> &other) {
		*this = other;
	}

	template <typename U>
	VectorBase &operator=(const Derived<U, N> &other) {
		std::copy(other.m_data, other.m_data + N, m_data);
		return *this;
	}

	T operator[](size_t i) const { return m_data[i]; }

	T &operator[](size_t i) { return m_data[i]; }

	// negate
	Vec operator-() const {
		Vec v("no init");
		for (size_t i = 0; i < N; i++) {
			v[i] = -m_data[i];
		}
		return v;
	}

	Vec operator+(const Vec &other) const {
		Vec v("no init");
		for (size_t i = 0; i < N; i++) {
			v[i] = m_data[i] + other[i];
		}
		return v;
	}

	Vec operator-(const Vec &other) const {
		Vec v("no init");
		for (size_t i = 0; i < N; i++) {
			v[i] = m_data[i] - other[i];
		}
		return v;
	}

	// scalar multiplication
	Vec operator*(T s) const {
		Vec v("no init");
		for (size_t i = 0; i < N; i++) {
			v[i] = m_data[i] * s;
		}
		return v;
	}

	Vec operator/(T s) const {
		Vec v("no init");
		for (size_t i = 0; i < N; i++) {
			v[i] = m_data[i] / s;
		}
		return v;
	}

	// dot product
	T operator*(const Vec &other) const {
		T s = 0;
		for (size_t i = 0; i < N; i++) {
			s += m_data[i] * other[i];
		}
		return s;
	}

	T dot(const Vec &other) const { return (*this) * other; }

	T magnitude() const {
		T s = 0;
		for (size_t i = 0; i < N; i++) {
			s += m_data[i] * m_data[i];
		}
		return std::sqrt(s);
	}

	Vec normalized() const {
		Vec v("no init");
		T mag = this->magnitude();
		for (size_t i = 0; i < N; i++) {
			v[i] = m_data[i] / mag;
		}
		return v;
	}
};

#define VECTOR_CTORS(Vector, T, N) \
private: \
	typedef VectorBase<T, N, ::Vector> Base; \
	friend Base; \
\
public: \
	Vector() : Base() {} \
\
	template <typename U> \
	Vector(const U(&a)[N]) : Base(a) {} \
\
	template <typename U> \
	Vector(const Vector<U, N> &other) : Base(other) {} \
\
private: \
	Vector(const char *s) : Base(s) {} // no init

#endif
