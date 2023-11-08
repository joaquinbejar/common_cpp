//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#ifndef COMMON_DATES_H
#define COMMON_DATES_H
#include <iostream>
#include <chrono>

namespace common::dates {
    time_t get_unix_timestamp(const int &seconds = 0);
}

#endif //COMMON_DATES_H
