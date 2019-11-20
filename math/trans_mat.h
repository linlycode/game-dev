#ifndef TRANS_MAT_H
#define TRANS_MAT_H

#include "vector.h"
#include "quat_mat.h"

namespace tfm {

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
		Quaternion<T> q = Quaternion<T>::rotate(axis, radian);
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
			{0, 0, -(far + near) / (far - near),
				-2 * far * near / (far - near)},
			{0, 0, -1, 0},
		};

		return a;
	}

	template <typename T>
	Matrix<T, 4, 4> perspective_projection_fov(T fovx, T fovy, T near, T far) {
		T tanx = std::tan(fovx / 2);
		T tany = std::tan(fovy / 2);

		T a[4][4] = {
			{1 / tanx, 0, 0, 0},
			{0, 1 / tany, 0, 0},
			{0, 0, -(far + near) / (far - near),
				-2 * far * near / (far - near)},
			{0, 0, -1, 0},
		};

		return a;
	}

	template <typename T>
	Matrix<T, 4, 4> perspective_projection_fovx(
		T fovx, T aspect, T near, T far) {
		T tanx = std::tan(fovx / 2);
		T tany = tanx / aspect;

		T a[4][4] = {
			{1 / tanx, 0, 0, 0},
			{0, 1 / tany, 0, 0},
			{0, 0, -(far + near) / (far - near),
				-2 * far * near / (far - near)},
			{0, 0, -1, 0},
		};

		return a;
	}

	template <typename T>
	Matrix<T, 4, 4> perspective_projection_fovy(
		T fovy, T aspect, T near, T far) {
		T tany = std::tan(fovy / 2);
		T tanx = tany * aspect;

		T a[4][4] = {
			{1 / tanx, 0, 0, 0},
			{0, 1 / tany, 0, 0},
			{0, 0, -(far + near) / (far - near),
				-2 * far * near / (far - near)},
			{0, 0, -1, 0},
		};

		return a;
	}
} // namespace tfm

#endif
