#include <catch2/catch.hpp>

#include "matrix.h"

namespace {
	const char *tags = "[math][matrix]";
}

TEST_CASE("matrix default constructor", tags) {
	Matrix<int, 2, 2> mat;
	CHECK(
		(mat(0, 0) == 0 && mat(0, 1) == 0 && mat(1, 0) == 0 && mat(1, 1) == 0));
}

TEST_CASE("matrix array constructor", tags) {
	int a[] = {1, 2, 3, 4, 5, 6};
	Matrix<int, 2, 3> mat1(a, ROW_MAJOR), mat2(a, COLUMN_MAJOR);

	CHECK((mat1(0, 0) == 1 && mat1(0, 1) == 2 && mat1(0, 2) == 3 &&
		   mat1(1, 0) == 4 && mat1(1, 1) == 5 && mat1(1, 2) == 6));

	CHECK((mat2(0, 0) == 1 && mat2(0, 1) == 3 && mat2(0, 2) == 5 &&
		   mat2(1, 0) == 2 && mat2(1, 1) == 4 && mat2(1, 2) == 6));
}

TEST_CASE("matrix 2D array constructor", tags) {
	int a[3][4] = {
		{8, -6, 3, 2},
		{5, 1, 0, -9},
		{4, -3, -1, 7},
	};

	Matrix<int, 3, 4> mat(a);

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 4; j++) {
			CHECK(mat(i, j) == a[i][j]);
		}
	}
}

TEST_CASE("matrix initializer list constructor", tags) {
	Matrix<int, 3, 2> mat{
		{2, -1},
		{3, 9},
		{-7, 0},
	};

	CHECK((mat(0, 0) == 2 && mat(0, 1) == -1 && mat(1, 0) == 3 &&
		   mat(1, 1) == 9 && mat(2, 0) == -7 && mat(2, 1) == 0));
}

TEST_CASE("identity matrix", tags) {
	auto mat = Matrix<int, 3, 3>::identity();

	CHECK((mat(0, 0) == 1 && mat(0, 1) == 0 && mat(0, 2) == 0 &&
		   mat(1, 0) == 0 && mat(1, 1) == 1 && mat(1, 2) == 0 &&
		   mat(2, 0) == 0 && mat(2, 1) == 0 && mat(2, 2) == 1));
}

TEST_CASE("matrix multiplication", tags) {
	Matrix<int, 2, 3> mat1{
		{2, -1, 5},
		{-7, 0, 6},
	};

	Matrix<int, 3, 2> mat2 = {
		{9, 1},
		{6, 8},
		{3, 7},
	};

	Matrix<int, 2, 2> mat3 = mat1 * mat2;

	CHECK((mat3(0, 0) == 27 && mat3(0, 1) == 29 && mat3(1, 0) == -45 &&
		   mat3(1, 1) == 35));
}

TEST_CASE("matrix transpose", tags) {
	Matrix<int, 2, 3> mat1{
		{2, -1, 5},
		{-7, 0, 6},
	};

	Matrix<int, 3, 2> mat2 = mat1.transpose();

	CHECK((mat2(0, 0) == 2 && mat2(0, 1) == -7 && mat2(1, 0) == -1 &&
		   mat2(1, 1) == 0 && mat2(2, 0) == 5 && mat2(2, 1) == 6));
}
