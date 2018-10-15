add_executable(raytracing image.h image.cpp ppm.h ppm.cpp raytracing.cpp)
target_include_directories(raytracing PRIVATE ${CMAKE_SOURCE_DIR})
