//
// Created by Joaquin Bejar Garcia on 25/12/23.
//
#include <common/common.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <common/dates.h>
#include <set>
#include <regex>

using common::dates::DateRange;

TEST_CASE("DateRange Print", "[DateRange]") {
    SECTION("all days") {
        DateRange dateRange(1); // 1 año
        for (const auto &dateStr: dateRange) {
            std::cout << dateStr << std::endl;
        }
    }
}

TEST_CASE("DateRange Tests", "[DateRange]") {
    SECTION("Format Check") {
        DateRange dateRange(1); // 1 año
        for (const auto &dateStr: dateRange) {
            std::regex dateFormat(R"(\d{4}-\d{2}-\d{2})");
            REQUIRE(std::regex_match(dateStr, dateFormat));
        }
    }

    SECTION("Weekend Exclusion") {
        DateRange dateRange(0);
        std::set<int> weekendDays = {0, 6};

        for (const auto& dateStr : dateRange) {
            std::tm tm = {};
            std::istringstream ss(dateStr);
            ss >> std::get_time(&tm, "%Y-%m-%d");
            std::time_t timeT = std::mktime(&tm);

            REQUIRE(weekendDays.find(tm.tm_wday) == weekendDays.end());
        }
    }

    SECTION("Correct Number of Days") {
        int years = 1;
        int expectedDays = 261; // 365 - 52*2
        DateRange dateRange(years);

        int dayCount = 0;
        for (auto it = dateRange.begin(); it != dateRange.end(); ++it) {
            dayCount++;
        }

        REQUIRE(dayCount <= expectedDays);
    }

    SECTION("Correct Number of Days 5 years ") {
        int years = 5;
        int expectedDays = 1305; // (365 - 52*2) * 5
        DateRange dateRange(years);

        int dayCount = 0;
        for (auto it = dateRange.begin(); it != dateRange.end(); ++it) {
            dayCount++;
        }

        REQUIRE(dayCount < expectedDays);
    }
}

TEST_CASE("Current and yesterday date", "[DateRange]") {
    SECTION("Current date") {
        std::string current_date = common::dates::get_current_date();
        std::regex dateFormat(R"(\d{4}-\d{2}-\d{2})");
        REQUIRE(std::regex_match(current_date, dateFormat));
        REQUIRE(current_date == "2023-12-28");
    }

    SECTION("Yesterday date") {
        std::string yesterday_date = common::dates::get_yesterday_date();
        std::regex dateFormat(R"(\d{4}-\d{2}-\d{2})");
        REQUIRE(std::regex_match(yesterday_date, dateFormat));
        REQUIRE(yesterday_date == "2023-12-27");
    }
}
