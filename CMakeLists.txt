cmake_minimum_required(VERSION 3.4)

project(ftpclient)

set(CMAKE_CXX_STANDARD 14)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 

add_executable(ftpclient main.cpp FTPClient.cpp)

install(TARGETS ftpclient RUNTIME DESTINATION bin)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
