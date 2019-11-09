find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

add_executable(glapp
	gl_loader.h gl_loader.cpp
	gl_err.h
	shader_util.h shader_util.cpp
	glfw_app.h glfw_app.cpp
	main.cpp
)

target_include_directories(glapp PRIVATE ${GLEW_INCLUDE_DIR} ${CMAKE_SOURCE_DIR})
target_link_libraries(glapp glfw glad OpenGL::GL infra)