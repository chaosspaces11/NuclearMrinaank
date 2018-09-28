cmake_minimum_required(VERSION 3.12)
project(NuclearMrinaank)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.64.0 COMPONENTS system filesystem thread REQUIRED)
find_package(OpenGL REQUIRED)



include_directories(/usr/local/include/GLFW)

find_library(GLFW3 libglfw.3.2.dylib PATHS /usr/local/Cellar/glfw/3.2.1/lib)

find_library(GLEW libGLEW.2.1.0.dylib PATHS /usr/local/Cellar/glew/2.1.0/lib)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLFW3}
        ${GLEW})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(NuclearMrinaank main.cpp Cell.h Cell.cpp Grid.cpp Grid.h CornerCell.cpp CornerCell.h SideCell.cpp SideCell.h Player.cpp Player.h PlayerManager.cpp PlayerManager.h)
add_executable(NuclearNetworkTest TestClient.cpp)
add_executable(NuclearOpenGLTest OpenGlTest.cpp)

if(Boost_FOUND)
    target_link_libraries(NuclearNetworkTest ${Boost_LIBRARIES})
endif()

target_link_libraries(NuclearOpenGLTest
        ${ALL_LIBS}
        )

