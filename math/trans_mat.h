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

template <typename T>
Matrix<T, 4, 4> ortho_projection(
	T left, T right, T bottom, T top, T near, T far) {

	T a[4][4] = {
		{2 / (right - left), 0, 0, -(right + left) / (right - left)},
		{0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom)},
		{0, 0, -2 / (far - near), -(far + near) / (far - near)},
		{0, 0, 0, 1},
	};

	return a;
}

template <typename T>
Matrix<T, 4, 4> perspective_projection(
	T left, T right, T bottom, T top, T near, T far) {

	T a[4][4] = {
		{2 * near / (right - left), 0, (right + left) / (right - left), 0},
		{0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0},
		{0, 0, -(far + near) / (far - near), -2 * far * near / (far - near)},
		{0, 0, -1, 0},
	};

	return a;
}

template <typename T>
Matrix<T, 4, 4> perspective_projection(T fovy, T aspect, T near, T far) {
	T tan = std::tan(fovy / 2);

	T a[4][4] = {
		{1 / (aspect * tan), 0, 0, 0},
		{0, 1 / tan, 0, 0},
		{0, 0, -(far + near) / (far - near), -2 * far * near / (far - near)},
		{0, 0, -1, 0},
	};

	return a;
}

#endif
