//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#ifndef COMMON_DATES_H
#define COMMON_DATES_H
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace common::dates {
    time_t get_unix_timestamp(const int &seconds = 0);

    std::string get_current_date();
}

#endif //COMMON_DATES_H
