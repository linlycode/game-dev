find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(glapp
	gl_loader.h gl_loader.cpp
	gl_err.h gl_err.cpp
	shader_util.h shader_util.cpp
	window.h window.cpp
	app.h app.cpp
	main.cpp
)

get_target_property(SDL2_INCLUDE_DIRS SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
get_filename_component(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} DIRECTORY)

target_include_directories(glapp PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(glapp SDL2::SDL2 glad OpenGL::GL infra)
