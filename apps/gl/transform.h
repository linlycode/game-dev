#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math/trans_mat.h"

template <typename T>
struct Transform {
	Vector<T, 3> translation;
	Quaternion<T> rotation;
	Vector<T, 3> scale;

	Transform(const Vector<T, 3> &trans = Vector<T, 3>(0, 0, 0),
		const Quaternion<T> &rot = Quaternion<T>::identity(),
		const Vector<T, 3> &scl = Vector<T, 3>(1, 1, 1))
		: translation(trans), rotation(rot), scale(scl) {}

	Matrix<T, 4, 4> toMatrix() const {
		return tfm::translate(translation) * quaternion_to_matrix(rotation) *
			   tfm::scale(scale);
	}
};

typedef Transform<float> Transformf;
typedef Transform<double> Transformd;

#endif
