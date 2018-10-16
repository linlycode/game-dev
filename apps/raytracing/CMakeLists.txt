add_executable(raytracing
	shape.h
	sphere.h sphere.cpp
	scene.h scene.cpp
	camera.h
	image.h image.cpp
	ppm.h ppm.cpp
	raytracing.cpp
)
target_include_directories(raytracing PRIVATE ${CMAKE_SOURCE_DIR})
