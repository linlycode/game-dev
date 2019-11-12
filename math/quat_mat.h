#ifndef QUAT_MAT_H
#define QUAT_MAT_H

#include "quaternion.h"
#include "matrix.h"

template <typename T>
Matrix<T, 4, 4> quaternion_to_matrix(const Quaternion<T> &quat) {
	const Vector<T, 3> &img = quat.image();
	T x = img[0], y = img[1], z = img[2], w = quat.real();

	T s = 2 / quat.norm();

	T a[4][4] = {
		{
			1 - s * (y * y + z * z),
			s * (x * y - w * z),
			s * (x * z + w * y),
			0,
		},
		{
			s * (x * y + w * z),
			1 - s * (x * x + z * z),
			s * (y * z - w * x),
			0,
		},
		{
			s * (x * z - w * y),
			s * (y * z + w * x),
			1 - s * (x * x + y * y),
			0,
		},
		{0, 0, 0, 1},
	};

	return a;
}

#endif
