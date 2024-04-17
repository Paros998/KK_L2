cmake_minimum_required(VERSION 3.27)
project(KK_L2)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Set GSL_ROOT to the directory where GSL is installed or extracted
set(GSL_ROOT "./libs/GSL/gsl-master/build/")
set(GSL_DIR "${GSL_ROOT}/cmake")

set(Boost_ROOT "./libs/boost_1_85_0")

find_package(GSL REQUIRED)
find_package(Boost REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
endif ()

include_directories(${GSL_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(KK_L2 src/main.cpp
        src/headers/Libraries.h

        src/headers/Arguments.h
        src/headers/FileService.h
        src/headers/NgramsUtil.h
        src/headers/Coder.h
        src/headers/CesarCoder.h
        src/headers/AffineCoder.h
        src/headers/App.h

        src/Arguments.cpp
        src/FileService.cpp
        src/NgramsUtil.cpp
        src/Coder.cpp
        src/CesarCoder.cpp
        src/App.cpp
        src/AffineCoder.cpp
)

target_link_libraries(KK_L2 ${GSL_LIBRARIES})

target_compile_features(KK_L2 PRIVATE cxx_std_23)