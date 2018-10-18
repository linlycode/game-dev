add_executable(raytracing
	random.h
	shape.h
	sphere.h sphere.cpp
	scene.h scene.cpp
	camera.h
	material.h
	materials/lambertian.h materials/lambertian.cpp
	materials/metal.h materials/metal.cpp
	image.h image.cpp
	ppm.h ppm.cpp
	raytracing.cpp
)

target_include_directories(raytracing PRIVATE ${CMAKE_SOURCE_DIR})
