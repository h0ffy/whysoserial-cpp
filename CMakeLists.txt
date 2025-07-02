cmake_minimum_required(VERSION 3.10)
project(whysoserial-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

add_executable(whysoserial-cpp src/whysoserial-cpp.cpp)

# Opcional: instalar el binario en /usr/local/bin
install(TARGETS whysoserial-cpp DESTINATION /usr/local/bin)
