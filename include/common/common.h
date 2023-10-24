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
#include <mutex>
#include <queue>
#include <thread>

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
    std::set<T> vector_to_set(const std::vector<T> &v) {
        return {v.begin(), v.end()};
    }


    template<typename T>
    std::set<T> join_sets(const std::set<T> &v1, const std::set<T> &v2) {
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
        for (const T &item: s) {
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


    template<typename T>
    class ThreadQueue {
    public:

        ThreadQueue(size_t timeout = 10) : m_timeout(timeout) {}

        bool enqueue(T t) {
            try {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_queue.push(t);
                return true;
            } catch (std::exception &e) {
                return false;
            }
        }

        bool dequeue_blocking(T &t) {
            while (m_queue.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(m_timeout));
            }
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_queue.empty()) {  // double-check
                return false;
            }
            t = m_queue.front();
            m_queue.pop();
            return true;
        }

        bool dequeue(T &t) {
            if (m_queue.empty()) {
                return false;
            }
            std::lock_guard<std::mutex> lock(m_mutex);
            t = m_queue.front();
            m_queue.pop();
            return true;
        }

    private:
        std::queue<T> m_queue;
        std::mutex m_mutex;
        size_t m_timeout;
    };

}

#endif //COMMON_COMMON_H
