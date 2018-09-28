cmake_minimum_required(VERSION 3.12)
project(NuclearMrinaank)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.67.0 COMPONENTS system filesystem thread REQUIRED)
find_package(OpenGL REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()


add_executable(NuclearMrinaank main.cpp Cell.h Cell.cpp Grid.cpp Grid.h CornerCell.cpp CornerCell.h SideCell.cpp SideCell.h Player.cpp Player.h PlayerManager.cpp PlayerManager.h Client.cpp Client.h)
add_executable(NuclearNetworkTest Server.cpp Server.h NetworkConnection.cpp NetworkConnection.h)
add_executable(NuclearNetworkTestClient Client.h Client.cpp)
add_executable(NuclearOpenGLTest OpenGlTest.cpp)

if(Boost_FOUND)
    target_link_libraries(NuclearNetworkTest ${Boost_LIBRARIES})
    target_link_libraries(NuclearNetworkTestClient ${Boost_LIBRARIES})

endif()

target_link_libraries(NuclearOpenGLTest ${OPENGL_LIBRARIES})

