cmake_minimum_required(VERSION 3.12)
project(NuclearMrinaank)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.64.0 COMPONENTS system filesystem thread REQUIRED)
find_package(OpenGL REQUIRED)

#include_directories(OpenGLDylib/glfw-3.2.1)
include_directories(OpenGLDylib/glfw-3.2.1/deps)
#include_directories(OpenGLDylib/glfw-3.2.1/src/CMakeFiles)

#find_package(glfw3 PATHS OpenGLDylib/glfw-3.2.1/src/CMakeFiles)

find_library(GLFW3 libglfw.3.2.dylib PATHS OpenGLDylib)
#
#find_library(GLEW libGLEW.2.1.0.dylib PATHS /usr/local/Cellar/glew/2.1.0/lib)
#
set(ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLFW3}
        )

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(NuclearMrinaank main.cpp Cell.h Cell.cpp Grid.cpp Grid.h CornerCell.cpp CornerCell.h SideCell.cpp SideCell.h Player.cpp Player.h PlayerManager.cpp PlayerManager.h OpenGlShader.h GraphicsManager.cpp GraphicsManager.h OpenGLDylib/glfw-3.2.1/deps/glad.c stb_image.cpp)
add_executable(NuclearNetworkTest TestClient.cpp)
add_executable(NuclearOpenGLTest OpenGlTest.cpp OpenGLDylib/glfw-3.2.1/deps/glad.c stb_image.cpp)
add_executable(NuclearMrinaankMultithreadTest  MultithreadTest.cpp)

if(Boost_FOUND)
    target_link_libraries(NuclearNetworkTest ${Boost_LIBRARIES})
endif()

target_link_libraries(NuclearOpenGLTest
        ${ALL_LIBS}
        )

target_link_libraries(NuclearMrinaank
        ${ALL_LIBS}
        )


