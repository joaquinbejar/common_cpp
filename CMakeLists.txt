cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(common)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(COMMON_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
if (CMAKE_DEBUG)
    message(STATUS "common CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
endif ()

include(FetchContent)
include(cmake/nlohmann_json.cmake)
include(cmake/simple_color.cmake)

add_library(common STATIC
        src/common.cpp include/common/common.h
        src/ip.cpp include/common/ip.h
        src/dates.cpp include/common/dates.h
        src/sql_utils.cpp include/common/sql_utils.h
        src/dates.cpp include/common/dates.h
)
target_include_directories(common
        PRIVATE
        ${COMMON_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
)
target_link_libraries(common
        PRIVATE
        simple_color
)

install(TARGETS common DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

option(NO_COMMON_TESTS "common Disable Current tests" OFF)

if (NOT NO_COMMON_TESTS)
    include(FetchContent)
    FetchContent_Declare(Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.4.0
    )
    FETCHCONTENT_GETPROPERTIES(Catch2)
    FETCHCONTENT_MAKEAVAILABLE(Catch2)

    add_subdirectory(test)
endif ()