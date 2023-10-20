//
// Created by Joaquin Bejar Garcia on 19/10/23.
//

#include <common/common.h>
#include <catch2/catch_test_macros.hpp>

// ---------------------------------------------------------------------------------------------------
TEST_CASE("Declare config", "[Common]") {

    REQUIRE(true);
}


TEST_CASE("to_upper works correctly", "[to_upper]") {
    using common::to_upper;

    SECTION("Mixed case") {
        REQUIRE(to_upper("HeLLo") == "HELLO");
    }

    SECTION("All lower") {
        REQUIRE(to_upper("world") == "WORLD");
    }

    SECTION("All upper") {
        REQUIRE(to_upper("WORLD") == "WORLD");
    }

    SECTION("Empty string") {
        REQUIRE(to_upper("").empty());
    }
}

TEST_CASE("to_lower works correctly", "[to_lower]") {
    using common::to_lower;

    SECTION("Mixed case") {
        REQUIRE(to_lower("HeLLo") == "hello");
    }

    SECTION("All lower") {
        REQUIRE(to_lower("world") == "world");
    }

    SECTION("All upper") {
        REQUIRE(to_lower("WORLD") == "world");
    }

    SECTION("Empty string") {
        REQUIRE(to_lower("").empty());
    }
}

TEST_CASE("to_hash works correctly", "[to_hash]") {
    using common::to_hash;

    SECTION("Non-empty strings") {
        REQUIRE(to_hash("hello") != to_hash("world"));
        REQUIRE(to_hash("hello") == to_hash("hello"));
    }

    SECTION("Empty string") {
        REQUIRE(to_hash("") == std::to_string(std::hash<std::string>{}("")));
    }
}


