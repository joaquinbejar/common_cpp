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





}