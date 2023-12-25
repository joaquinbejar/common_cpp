
add_executable(test_common test_common.cpp)
target_include_directories(test_common
        PRIVATE
        ${COMMON_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
)

target_link_libraries(test_common PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_common PRIVATE
        common
        simple_color
)

add_executable(test_ip test_ip.cpp)
target_include_directories(test_ip
        PRIVATE
        ${COMMON_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
)

target_link_libraries(test_ip PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_ip PRIVATE
        common
)

add_executable(test_sql_utils test_sql_utils.cpp)
target_include_directories(test_sql_utils
        PRIVATE
        ${COMMON_INCLUDE}
)

target_link_libraries(test_sql_utils PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_sql_utils PRIVATE
        common
)

add_executable(test_dates test_dates.cpp)
target_include_directories(test_dates
        PRIVATE
        ${COMMON_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
)

target_link_libraries(test_dates PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_dates PRIVATE
        common
)