
FetchContent_Declare(Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.83.0
)
FETCHCONTENT_GETPROPERTIES(Boost)
FETCHCONTENT_MAKEAVAILABLE(Boost)
set(BOOST_SOURCE_DIR ${Boost_SOURCE_DIR} CACHE INTERNAL "")
set(BOOST_ASIO_INCLUDE ${BOOST_SOURCE_DIR}/libs/asio/include CACHE INTERNAL "")
message(STATUS "BOOST_INCLUDE ${BOOST_ASIO_INCLUDE}")

#find_package(Boost REQUIRED COMPONENTS system)
