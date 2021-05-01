cmake_minimum_required(VERSION 3.18)

project(cancellation)

#
# Dependencies
#

include (FetchContent)
FetchContent_Declare(asio_src
        URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-18-1.tar.gz)
if (NOT "${asio_src}_POPULATED")
    FetchContent_Populate(asio_src)
endif()
message(STATUS "[asio] asio_src_SOURCE_DIR: ${asio_src_SOURCE_DIR}")
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE "${asio_src_SOURCE_DIR}/asio/include")

foreach(my_project asio_way)
    add_subdirectory("${my_project}")
endforeach()