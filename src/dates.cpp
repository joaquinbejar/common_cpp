//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#include "common/dates.h"

namespace common::dates {

    // Function to get the Unix timestamp, optionally adjusted by a number of seconds
    time_t get_unix_timestamp(const int &seconds) {
        // Get the current system time as a time point
        auto now = std::chrono::system_clock::now();

        // Adjust the time by the given number of seconds
        auto adjusted_now = now + std::chrono::seconds(seconds);

        // Convert the adjusted time to time since epoch and then to time_t
        auto time_t_now = std::chrono::system_clock::to_time_t(adjusted_now);

        // Return the time as time_t
        return time_t_now;
    }

    std::string get_current_date() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm now_tm = *std::localtime(&now_time);

        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d");

        return ss.str();
    }

    bool isWeekend(const std::chrono::system_clock::time_point &date) {
        auto timeT = std::chrono::system_clock::to_time_t(date);
        auto localTime = *std::localtime(&timeT);
        return localTime.tm_wday == 0 || localTime.tm_wday == 6; // Sunday or Saturday
    }

    std::string formatDate(const std::chrono::system_clock::time_point &date) {
        auto timeT = std::chrono::system_clock::to_time_t(date);
        std::tm tm = *std::localtime(&timeT);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }

    DateIterator::DateIterator(int daysToEnd)
            : date_(std::chrono::system_clock::now()),
              endDate_(date_ - std::chrono::days(daysToEnd)) {}

    DateIterator::Date DateIterator::operator*() {
        return formatDate(date_);
    }

    DateIterator &DateIterator::operator++() {
        do {
            date_ -= std::chrono::days(1);
        } while (isWeekend(date_));
        return *this;
    }

    DateIterator DateIterator::operator++(int) {
        DateIterator temp = *this;
        ++(*this);
        return temp;
    }


    DateRange::DateRange(int years) : years_(years) {}

    DateIterator DateRange::begin() {
        return DateIterator(0);
    }

    DateIterator DateRange::end()  {
        return DateIterator(years_ * 365); // Simplification, does not account for leap years
    }

}