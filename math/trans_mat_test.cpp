#include <catch2/catch.hpp>

#include "mat_test_helper.h"
#include "trans_mat.h"

TEST_CASE("translate", "[math]") {
	float a[4][4] = {
		{1, 0, 0, 1},
		{0, 1, 0, 2},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};

	Matrix4f expected(a);

	CHECK(mat_equal(translate(Vector3f(1, 2, 0)), expected));
}

TEST_CASE("rotate", "[math]") {
	Vector3f axis(0, 1, 0);
	float angle = static_cast<float>(M_PI) / 2;
	float sin = std::sin(angle), cos = std::cos(angle);

	float a[4][4] = {
		{cos, 0, sin, 0},
		{0, 1, 0, 0},
		{-sin, 0, cos, 0},
		{0, 0, 0, 1},
	};

	Matrix4f expected(a);

	CHECK(mat_equal(rotate(axis, angle), expected));
}

TEST_CASE("scale", "[math]") {
	Vector3f(0.5f, 0.5f, 0.3f);

	float a[4][4] = {
		{0.5f, 0, 0, 0},
		{0, 0.5f, 0, 0},
		{0, 0, 0.3f, 0},
		{0, 0, 0, 1},
	};

	Matrix4f expected(a);

	CHECK(mat_equal(scale(Vector3f(0.5f, 0.5f, 0.3f)), expected));
}
