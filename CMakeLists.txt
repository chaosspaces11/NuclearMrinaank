cmake_minimum_required(VERSION 3.12)
project(NuclearMrinaank)

set(CMAKE_CXX_STANDARD 17)

add_executable(NuclearMrinaank main.cpp Cell.h Cell.cpp Grid.cpp Grid.h Debug.h CornerCell.cpp CornerCell.h SideCell.cpp SideCell.h Player.cpp Player.h PlayerManager.cpp PlayerManager.h)