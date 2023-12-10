cmake_minimum_required(VERSION 3.3)
project(bfetch VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c")
add_executable(bfetch ${SRC_FILES})
