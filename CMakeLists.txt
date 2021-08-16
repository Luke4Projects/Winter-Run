cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(C:/OpenGL/include)
link_directories(C:/OpenGL/lib)

add_executable(game 

C:/OpenGL/glad.c

src/main.cpp
src/game.cpp src/include/game.h
src/shader.cpp src/include/shader.h
src/input.cpp src/include/input.h
src/entity.cpp src/include/entity.h
src/camera.cpp src/include/camera.h
src/particle.cpp src/include/particle.h
src/text_renderer.cpp src/include/text_renderer.h
src/render.cpp
src/menu.cpp

)

target_link_libraries(game glfw3.lib opengl32.lib freetyped.lib winmm.lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
