//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#include <common/sql_utils.h>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("'' is replaced by NULL", "[common::empty_to_null]") {
    SECTION("Replaces Empty Correctly") {
        std::string query = "VALUES ('true', '', '', 'usd');";
        std::string expected = "VALUES ('true', NULL, NULL, 'usd');";
        REQUIRE(common::sql_utils::empty_to_null(query) == expected);
    }

    SECTION("No Replacement Needed") {
        std::string query = "VALUES ('true', 'data', 'more data', 'usd');";
        std::string expected = query; // No change expected
        REQUIRE(common::sql_utils::empty_to_null(query) == expected);
    }

    SECTION("Empty String") {
        std::string query ;
        std::string expected ;
        REQUIRE(common::sql_utils::empty_to_null(query) == expected);
    }

    SECTION("Similar But Not Empty") {
        std::string query = "VALUES (' ', '  ', '   ');";
        std::string expected = "VALUES (' ', '  ', '   ');"; // No change expected
        REQUIRE(common::sql_utils::empty_to_null(query) == expected);
    }
}
