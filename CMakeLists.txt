cmake_minimum_required(VERSION 3.3)
project(lidar)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

find_package(
    OpenCV REQUIRED
)

include_directories(
    include/
    ${OpenCV_INCLUDE_DIRS}
)

set(SOURCES
    src/main.cpp
    src/environment.cpp
    src/robot.cpp
    src/simulation.cpp
    src/map.cpp
)

set(HEADERS
    include/types.hpp
    include/environment.hpp
    include/robot.hpp
    include/simulation.hpp
    include/map.hpp
)

add_executable( main ${SOURCES} ${HEADERS} )
target_link_libraries( main ${OpenCV_LIBS} )