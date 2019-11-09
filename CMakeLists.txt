cmake_minimum_required(VERSION 3.13)

project(GameDev)

option(BUILD_APPS "Build apps" ON)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

if (BUILD_TESTS)
	find_package(Catch2)

	add_executable(tests test_main.cpp)
	add_subdirectory(math)

	target_link_libraries(tests Catch2::Catch2)
endif()

if (BUILD_APPS)
	add_subdirectory(infra)
	add_subdirectory(third_party/glad)
	add_subdirectory(apps)
endif()
