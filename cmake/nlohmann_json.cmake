


FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)
set(NLOHMANN_JSON_SOURCE_DIR ${nlohmann_json_SOURCE_DIR} CACHE INTERNAL "")
set(NLOHMANN_JSON_INCLUDE ${NLOHMANN_JSON_SOURCE_DIR}/single_include CACHE INTERNAL "")
message(STATUS "NLOHMANN_JSON_INCLUDE ${NLOHMANN_JSON_INCLUDE}")
