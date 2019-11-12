#ifndef TRANS_MAT_H
#define TRANS_MAT_H

#include <cmath>

#include "vector.h"
#include "quat_mat.h"

template <typename T>
Matrix<T, 4, 4> translate(const Vector<T, 3> &t) {
	T a[4][4] = {
		{1, 0, 0, t[0]},
		{0, 1, 0, t[1]},
		{0, 0, 1, t[2]},
		{0, 0, 0, 1},
	};

	return a;
}

template <typename T>
Matrix<T, 4, 4> rotate(const Vector<T, 3> &axis, T radian) {
	T angle = radian / 2;
	Quaternion<T> q(std::sin(angle) * axis.normalized(), std::cos(angle));
	return quaternion_to_matrix(q);
}

template <typename T>
Matrix<T, 4, 4> scale(const Vector<T, 3> &s) {
	T a[4][4] = {
		{s[0], 0, 0, 0},
		{0, s[1], 0, 0},
		{0, 0, s[2], 0},
		{0, 0, 0, 1},
	};

	return a;
}

#endif
