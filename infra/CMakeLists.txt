set(SOURCES fmt.h fmt.cpp filepath.h filepath.cpp)

add_library(infra STATIC ${SOURCES})

if (BUILD_TESTS)
	target_sources(tests PRIVATE ${SOURCES} fmt_test.cpp)
endif()
