
include_directories(src)
file(GLOB_RECURSE my_src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(asio_way ${my_src_files})
target_link_libraries(asio_way PRIVATE Boost::system Boost::thread)

