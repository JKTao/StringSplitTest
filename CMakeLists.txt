cmake_minimum_required(VERSION 2.8) 
project(StringSplitTest)
set(CMAKE_CXX_FLAGS " -O2  -march=native")
find_package(Boost REQUIRED)
include_directories(${BOOST_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/include")

add_executable(StringSplitTest test.cc)
target_link_libraries(StringSplitTest ${BOOST_LIBRARIES})