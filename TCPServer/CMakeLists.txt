cmake_minimum_required(VERSION 3.23)
project(TCPServer)

set(CMAKE_CXX_STANDARD 98)

add_executable(TCPServer main.cpp Server.cpp Server.h Client.cpp Client.h)
