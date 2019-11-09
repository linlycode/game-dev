#ifndef MATRIX_H
#define MATRIX_H

#include "mat_base.h"

template <typename T, size_t M, size_t N>
class Matrix : public MatrixBase<T, M, N, Matrix> {
	MATRIX_CTORS(Matrix, T, M, N)
};

template <typename T, size_t N>
class Matrix<T, N, N> : public MatrixBase<T, N, N, Matrix> {
	MATRIX_CTORS(Matrix, T, N, N)

public:
	static Matrix identity() {
		Matrix m;
		for (size_t i = 0; i < N; i++) {
			m(i, i) = 1;
		}
		return m;
	}
};

typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;

typedef Matrix<double, 2, 2> Matrix2d;
typedef Matrix<double, 3, 3> Matrix3d;
typedef Matrix<double, 4, 4> Matrix4d;

#endif
