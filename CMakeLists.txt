cmake_minimum_required(VERSION 3.0)

project(ftpclient)

add_executable(ftpclient main.cpp)

install(TARGETS ftpclient RUNTIME DESTINATION bin)
