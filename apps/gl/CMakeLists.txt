find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(glapp
	gl_loader.h gl_loader.cpp
	gl_err.h gl_err.cpp
	transform.h
	shader_util.h shader_util.cpp
	key_state.h
	keyboard_keys.h
	mouse_input.h
	window.h window.cpp
	app.h app.cpp
	camera.h camera.cpp
	camera_controller.h camera_controller.cpp
	mouse_input_handler.h mouse_input_handler.cpp
	keyboard_input_handler.h keyboard_input_handler.cpp
	main.cpp
)

get_target_property(SDL2_INCLUDE_DIRS SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
get_filename_component(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} DIRECTORY)

target_include_directories(glapp PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(glapp SDL2::SDL2 glad OpenGL::GL infra)
