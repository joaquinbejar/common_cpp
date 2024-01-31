//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#include "common/dates.h"

namespace common::dates {

    bool is_valid_date_format(const std::string &date) {
        std::regex date_format_regex(R"(\d{4}-\d{2}-\d{2})");

        return std::regex_match(date, date_format_regex);
    }

    std::string epoch_to_date_string(long long epoch) {
        if (epoch > 10000000000) {
            epoch /= 1000;
        }

        std::chrono::time_point<std::chrono::system_clock> tp = std::chrono::system_clock::from_time_t(epoch);

        std::time_t time = std::chrono::system_clock::to_time_t(tp);
        std::tm *tm_ptr = std::localtime(&time);

        std::ostringstream oss;
        oss << std::put_time(tm_ptr, "%Y-%m-%d");

        return oss.str();
    }

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

    date_format_t get_current_date() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm now_tm = *std::localtime(&now_time);

        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d");

        return ss.str();
    }

    date_format_t get_yesterday_date() {
        auto now = std::chrono::system_clock::now();
        // Resta un día (24 horas)
        auto yesterday = now - std::chrono::hours(24);
        std::time_t yesterday_time = std::chrono::system_clock::to_time_t(yesterday);

        std::tm yesterday_tm = *std::localtime(&yesterday_time);

        std::stringstream ss;
        ss << std::put_time(&yesterday_tm, "%Y-%m-%d");

        return ss.str();
    }

    date_format_t get_date_days_ago(size_t daysAgo) {
        auto now = std::chrono::system_clock::now();

        auto yesterday = now - std::chrono::hours(24 * daysAgo);
        std::time_t yesterday_time = std::chrono::system_clock::to_time_t(yesterday);

        std::tm yesterday_tm = *std::localtime(&yesterday_time);

        std::stringstream ss;
        ss << std::put_time(&yesterday_tm, "%Y-%m-%d");

        return ss.str();
    }


    bool isWeekend(const std::chrono::system_clock::time_point &date) {
        auto timeT = std::chrono::system_clock::to_time_t(date);
        auto localTime = *std::localtime(&timeT);
        return localTime.tm_wday == 0 || localTime.tm_wday == 6; // Sunday or Saturday
    }

    date_format_t formatDate(const std::chrono::system_clock::time_point &date) {
        auto timeT = std::chrono::system_clock::to_time_t(date);
        std::tm tm = *std::localtime(&timeT);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }

    DateIterator::DateIterator(size_t daysToEnd)
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

    DateRange::DateRange(size_t years) : years_(years) {}

    DateIterator DateRange::begin() {
        return DateIterator(0);
    }

    DateIterator DateRange::end() {
        return DateIterator(years_ * 365); // Simplification, does not account for leap years
    }

    unsigned long long date_to_timestamp(const date_format_t &date, long long offset) {
        if (date.empty()) {
            throw std::runtime_error("Date is empty.");
        }

        std::tm tm = {};
        std::stringstream ss(date);

        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (!is_valid_date_format(date) || ss.fail()) {
            throw std::runtime_error("Date format is invalid.");
        }

        std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        return std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() + offset;
    }

}