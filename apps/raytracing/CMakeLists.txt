add_executable(raytracing
	random.h
	shape.h
	sphere.h sphere.cpp
	scene.h scene.cpp
	camera.h
	optics.h optics.cpp
	material.h
	materials/lambertian.h materials/lambertian.cpp
	materials/metal.h materials/metal.cpp
	materials/dielectric.h materials/dielectric.cpp
	image.h image.cpp
	ppm.h ppm.cpp
	raytracing.cpp
)

target_include_directories(raytracing PRIVATE ${CMAKE_SOURCE_DIR})
