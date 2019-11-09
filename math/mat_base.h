#ifndef MAT_BASE_H
#define MAT_BASE_H

#include <initializer_list>
#include <algorithm>

enum StorageOrder { ROW_MAJOR, COLUMN_MAJOR };

template <typename T, size_t M, size_t N,
	template <typename, size_t, size_t> class Derived>
class MatrixBase {
private:
	typedef Derived<T, M, N> Mat;
	friend MatrixBase<T, N, M, Derived>;

protected:
	MatrixBase(const char *) {} // no init

private:
	T m_data[M * N];

public:
	MatrixBase() { std::fill(m_data, m_data + M * N, 0); }

	template <typename U>
	MatrixBase(const U (&a)[M * N], StorageOrder order) {
		assign(a, order);
	}

	template <typename U>
	MatrixBase(const U (&a)[M][N]) {
		*this = a;
	}

	template <typename U>
	MatrixBase(std::initializer_list<std::initializer_list<U>> list)
		: MatrixBase() {
		size_t m = std::min(list.size(), M);

		for (size_t i = 0; i < m; i++) {
			const std::initializer_list<U> *row = list.begin() + i;
			size_t n = std::min(row->size(), N);

			for (size_t j = 0; j < n; j++) {
				(*this)(i, j) = *(row->begin() + j);
			}
		}
	}

	MatrixBase(const MatrixBase &other) {
		std::copy(other.m_data, other.m_data + M * N, m_data);
	}

	template <typename U>
	MatrixBase &assign(const U (&a)[M * N], StorageOrder order) {
		if (order == COLUMN_MAJOR) {
			std::copy(a, a + M * N, m_data);
		} else {
			for (size_t i = 0; i < M * N; i++) {
				size_t row = i % M, col = i / M;
				m_data[i] = a[row * N + col];
			}
		}
		return *this;
	}

	template <typename U>
	MatrixBase &operator=(const U (&a)[M][N]) {
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				(*this)(i, j) = a[i][j];
			}
		}
		return *this;
	}

	T operator()(size_t i, size_t j) const { return m_data[j * M + i]; }

	T &operator()(size_t i, size_t j) { return m_data[j * M + i]; }

	// negate
	Mat operator-() const {
		Mat m("no init");
		for (size_t i = 0; i < M * N; i++) {
			m.m_data[i] = -m_data[i];
		}
		return m;
	}

	Mat operator*(T s) const {
		Mat m("no init");
		for (size_t i = 0; i < M * N; i++) {
			m.m_data[i] = m_data[i] * s;
		}
		return m;
	}

	Mat operator/(T s) const {
		Mat m("no init");
		for (size_t i = 0; i < M * N; i++) {
			m.m_data[i] = m_data[i] / s;
		}
		return m;
	}

	Mat operator+(const Mat &other) const {
		Mat m("no init");
		for (size_t i = 0; i < M * N; i++) {
			m.m_data[i] = m_data[i] + other.m_data[i];
		}
		return m;
	}

	Mat operator-(const Mat &other) const {
		Mat m("no init");
		for (size_t i = 0; i < M * N; i++) {
			m.m_data[i] = m_data[i] - other.m_data[i];
		}
		return m;
	}

	template <size_t O>
	Derived<T, M, O> operator*(const Derived<T, N, O> &other) const {
		Derived<T, M, O> m;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < O; j++) {
				T s = 0;
				for (size_t k = 0; k < N; k++) {
					s += (*this)(i, k) * other(k, j);
				}
				m(i, j) = s;
			}
		}
		return m;
	}

	Derived<T, N, M> transpose() const {
		Derived<T, N, M> m("no init");
		for (size_t i = 0; i < M * N; i++) {
			size_t row = i / N, col = i % N;
			m.m_data[i] = m_data[col * M + row];
		}
		return m;
	}
};

#define MATRIX_CTORS(Matrix, T, M, N) \
private: \
	typedef MatrixBase<T, M, N, ::Matrix> Base; \
	friend Base; \
	friend MatrixBase<T, N, M, ::Matrix>; \
\
public: \
	Matrix() : Base() {} \
\
	template <typename U> \
	Matrix(const U(&a)[M * N], StorageOrder order) : Base(a, order) {} \
\
	template <typename U> \
	Matrix(const U(&a)[M][N]) : Base(a) {} \
\
	template <typename U> \
	Matrix(std::initializer_list<std::initializer_list<U>> list) \
		: Base(list) {} \
\
	template <typename U> \
	Matrix(const Matrix<U, M, N> &other) : Base(other) {} \
\
private: \
	Matrix(const char *s) : Base(s) {} // no init

#endif
