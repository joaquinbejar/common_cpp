//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#ifndef COMMON_DATES_H
#define COMMON_DATES_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <iterator>
#include <regex>

namespace common::dates {

    typedef std::string date_format_t;

    bool is_valid_date_format(const std::string &date);

    std::string epoch_to_date_string(long long epoch);

    time_t get_unix_timestamp(const int &seconds = 0);

    date_format_t get_current_date();

    date_format_t get_yesterday_date();

    date_format_t get_date_days_ago(size_t daysAgo);

    bool isWeekend(const std::chrono::system_clock::time_point &date);

    date_format_t formatDate(const std::chrono::system_clock::time_point &date);

    class DateIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using Date = std::string;
        using pointer = const Date *;
        using reference = const Date &;

        explicit DateIterator(size_t daysAgo);

        DateIterator() = delete;

        Date operator*();

        DateIterator &operator++();

        DateIterator operator++(int);

        friend bool operator==(const DateIterator &a, const DateIterator &b) {
            return a.date_ == b.date_;
        }

        friend bool operator!=(const DateIterator &a, const DateIterator &b) {
            return a.date_ > b.endDate_;
        }

    private:
        std::chrono::system_clock::time_point date_;
        std::chrono::system_clock::time_point endDate_;
    };

    class DateRange {
    public:
        explicit DateRange(size_t years);

        DateIterator begin();

        [[nodiscard]] DateIterator end();

    private:
        int years_;
    };

    unsigned long long date_to_timestamp(const date_format_t& date, long long offset = 0);

}

#endif //COMMON_DATES_H
