//
// Created by Joaquin Bejar Garcia on 19/10/23.
//

#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include "nlohmann/json.hpp"
#include <set>
#include "simple_color/color.h"
#include <iostream>
#include <sstream>
#include <random>

using json = nlohmann::json;

namespace common {
    class TimerSimple {
    public:
        explicit TimerSimple();

        ~TimerSimple();

        std::string Get();

        std::string GetNC();

    private:
        time_t m_begin{}, m_end{};
    };

    class Timer {
    public:
        explicit Timer(std::string string);

        ~Timer();

    private:
        std::chrono::steady_clock::time_point begin{};
        std::string m_string{};
    };

    template<typename T>
    std::string set_precision_t(T value, int precision) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision) << value;
        return ss.str();
    }

    template<typename T>
    std::set<T> vector_to_set(const std::vector<T>& v) {
        return {v.begin(), v.end()};
    }


    template<typename T>
    std::set<T> join_sets(const std::set<T>& v1, const std::set<T>& v2) {
        std::set<T> output;
        std::set_union(v1.begin(), v1.end(),
                       v2.begin(), v2.end(),
                       std::inserter(output, output.begin()));
        return output;
    }


    template<typename T>
    std::string to_string_for_json(const T &item) {
        return std::to_string(item);
    }

    std::string to_string_for_json(const std::string &item);

    template<typename T>
    std::string set_to_json(std::set<T> s) {
        std::string output = "[";
        for (const T &item : s) {
            output.append(to_string_for_json(item));
            output.append(",");
        }
        if (!s.empty()) {
            output.erase(output.end() - 1);  // remove last comma
        }
        output.append("]");
        return output;
    }

    std::string to_upper(const std::string &str);

    std::string to_lower(const std::string &str);

    std::string to_hash(const std::string &str);

    std::string key_generator();

    std::string get_env_variable_string(std::string const &key, std::string const &default_value);

    std::set<std::string> get_env_variable_set_string(std::string const &key, std::string const &default_value);

    int get_env_variable_int(std::string const &key, int const &default_value);

    unsigned long long get_env_variable_long(std::string const &key, int const &default_value);

    bool get_env_variable_bool(std::string const &key, bool const &default_value);

}

#endif //COMMON_COMMON_H
