include(FetchContent)
FetchContent_Declare(simple_color
        GIT_REPOSITORY https://github.com/joaquinbejar/simple_color.git
        GIT_TAG v0.1.1
)
FetchContent_MakeAvailable(simple_color)

set(SIMPLE_COLOR_INCLUDE ${simple_color_SOURCE_DIR}/include CACHE INTERNAL "")
if (CMAKE_DEBUG)
    message(STATUS "common/cmake SIMPLE_COLOR_SOURCE_DIR ${simple_color_SOURCE_DIR}")
    message(STATUS "common/cmake SIMPLE_COLOR_INCLUDE ${SIMPLE_COLOR_INCLUDE}")
endif ()
