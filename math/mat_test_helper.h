#ifndef MAT_TEST_HELPER
#define MAT_TEST_HELPER

#include <cmath>

#include "test_helper.h"
#include "matrix.h"

template <typename T, size_t M, size_t N>
bool mat_equal(const Matrix<T, M, N> &m1, const Matrix<T, M, N> &m2) {
	for (size_t i = 0; i < M; i++) {
		for (size_t j = 0; j < N; j++) {
			if (m1(i, j) != m2(i, j)) {
				return false;
			}
		}
	}
	return true;
}

template <size_t M, size_t N>
bool mat_equal(const Matrix<float, M, N> &m1, const Matrix<float, M, N> &m2) {
	for (size_t i = 0; i < M; i++) {
		for (size_t j = 0; j < N; j++) {
			if (!almost_equal(m1(i, j), m2(i, j))) {
				return false;
			}
		}
	}
	return true;
}

#endif
