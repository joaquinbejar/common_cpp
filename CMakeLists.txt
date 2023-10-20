cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(common)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(COMMON_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")

include(FetchContent)
include(cmake/nlohmann_json.cmake)
#include(cmake/boost.cmake)
include(cmake/simple_color.cmake)

message(STATUS "SIMPLE_COLOR_INCLUDE ${SIMPLE_COLOR_INCLUDE}")

add_library(common STATIC
        src/common.cpp include/common/common.h
        src/ip.cpp include/common/ip.h
        src/dates.cpp include/common/dates.h
)
target_include_directories(common
        PRIVATE
        ${COMMON_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
#        ${BOOST_ASIO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
)

install(TARGETS common DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

option(NO_COMMON_TESTS "Disable Current tests" OFF)

if (NOT NO_COMMON_TESTS)

    FetchContent_Declare(Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.4.0
    )
    FETCHCONTENT_GETPROPERTIES(Catch2)
    FETCHCONTENT_MAKEAVAILABLE(Catch2)

    add_subdirectory(test)
endif ()