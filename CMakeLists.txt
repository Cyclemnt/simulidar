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
    src/lidar.cpp
)

set(HEADERS
    include/types.hpp
    include/environment.hpp
    include/robot.hpp
    include/simulation.hpp
    include/map.hpp
    include/lidar.hpp
)

set(CMAKE_BUILD_TYPE Debug) 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")  

add_executable( main ${SOURCES} ${HEADERS} )
target_link_libraries( main ${OpenCV_LIBS} )