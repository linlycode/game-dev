#include <catch2/catch.hpp>

#include "fmt.h"

TEST_CASE("fmt::sprintf", "[infra][fmt]") {
	CHECK(fmt::sprintf("hello %s", "world") == "hello world");
}
