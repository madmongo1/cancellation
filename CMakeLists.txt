cmake_minimum_required(VERSION 3.18)

project(cancellation)

#
# Dependencies
#

include(cmake/RequireBoost.cmake)
set(my_prefix_path "${PROJECT_BINARY_DIR}/_deps")
list(APPEND CMAKE_PREFIX_PATH "${my_prefix_path}")
set(my_boost_components COMPONENTS system thread)
if (my_boost_components)
    set(my_boost_components_cmd COMPONENTS ${my_boost_components})
endif()
foreach(my_component IN LISTS my_boost_components)
    list(APPEND my_boost_libs "Boost::${my_component}")
endforeach()
RequireBoost(PREFIX "${PROJECT_BINARY_DIR}/_deps" VERSION 1.76.0 ${my_boost_components_cmd})
find_package(Boost COMPONENTS ${my_boost_components_cmd} REQUIRED CONFIG)
message(STATUS "[boost] Version ${Boost_VERSION}")
message(STATUS "[boost] Include ${Boost_INCLUDE_DIRS}")
message(STATUS "[boost] Libraries ${Boost_LIBRARIES}")

#
# Projects
#

foreach(my_project asio_way)
    add_subdirectory("${my_project}")
endforeach()