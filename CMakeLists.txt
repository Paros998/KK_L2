cmake_minimum_required(VERSION 3.27)
project(KK_L2)

set(CMAKE_CXX_STANDARD 23)

add_executable(KK_L2 src/main.cpp
        src/headers/Libraries.h

        src/headers/Arguments.h
        src/headers/FileService.h
        src/headers/Coder.h
        src/headers/App.h

        src/Arguments.cpp
        src/FileService.cpp
        src/Coder.cpp
        src/App.cpp
)
