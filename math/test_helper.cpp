#include <cmath>
#include "test_helper.h"

#define EPSILON 0.0000001f

bool almost_equal(float a, float b) { return std::fabs(a - b) < EPSILON; }
