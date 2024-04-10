cmake_minimum_required(VERSION 3.27)
project(KK_L2)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Set GSL_ROOT to the directory where GSL is installed or extracted
set(GSL_ROOT "libs/GSL/gsl-master/build/")
set(GSL_DIR "${GSL_ROOT}/cmake")

find_package(GSL REQUIRED)

include_directories(${GSL_INCLUDE_DIRS})

add_executable(KK_L2 src/main.cpp
        src/headers/Libraries.h

        src/headers/Arguments.h
        src/headers/FileService.h
        src/headers/NgramsUtil.h
        src/headers/CesarCoder.h
        src/headers/App.h

        src/Arguments.cpp
        src/FileService.cpp
        src/NgramsUtil.cpp
        src/CesarCoder.cpp
        src/App.cpp
)

target_link_libraries(KK_L2 ${GSL_LIBRARIES})