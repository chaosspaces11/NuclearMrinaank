cmake_minimum_required(VERSION 3.12)
project(NuclearMrinaank)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.64.0 COMPONENTS system filesystem thread REQUIRED)
find_package(OpenGL REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(NuclearMrinaank main.cpp Cell.h Cell.cpp Grid.cpp Grid.h CornerCell.cpp CornerCell.h SideCell.cpp SideCell.h Player.cpp Player.h PlayerManager.cpp PlayerManager.h)
add_executable(NuclearNetworkTest TestClient.cpp)
add_executable(NuclearOpenGLTest OpenGlTest.cpp)

if(Boost_FOUND)
    target_link_libraries(NuclearNetworkTest ${Boost_LIBRARIES})
endif()

target_link_libraries(NuclearOpenGLTest ${OPENGL_LIBRARIES})

