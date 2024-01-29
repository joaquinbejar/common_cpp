//
// Created by Joaquin Bejar Garcia on 19/10/23.
//

#include "common/common.h"

namespace common {
    TimerSimple::TimerSimple() {
        std::time(&m_begin);
    }

    TimerSimple::~TimerSimple() = default;

    std::string TimerSimple::Get() {
        std::time(&m_end);
        set_precision_t(std::difftime(m_end, m_begin), 2);
        return simple_color::give_color(simple_color::Colors::YELLOW,
                                        set_precision_t(std::difftime(m_end, m_begin), 2));
    }

    std::string TimerSimple::GetNC() {
        std::time(&m_end);
        return set_precision_t(std::difftime(m_end, m_begin), 10);
    }

    Timer::Timer(std::string string) : m_string(std::move(string)) {
        begin = std::chrono::steady_clock::now();
    }

    Timer::~Timer() {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();

        std::cout << simple_color::LightCyan1 << m_string << ": " << simple_color::White << seconds << "[s]"
                  << simple_color::Normal << std::endl;
    }

    std::string to_upper(const std::string &str) {
        std::string result(str.size(), ' ');
        std::transform(str.begin(), str.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    std::string to_lower(const std::string &str) {
        std::string result(str.size(), ' ');
        std::transform(str.begin(), str.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    std::string to_hash(const std::string &str) {
        std::hash<std::string> hashFn;
        std::size_t hashValue = hashFn(str);
        return std::to_string(hashValue);
    }

    std::string key_generator() {
        std::string abc = "abcdefghijklmnopqrstuvwxyz";
        int size = 20;
        int each = 5;
        std::string key;
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = 0; i < size; i++) {
            if (i > 0 && i % each == 0) {
                key += "_";
            }
            std::uniform_int_distribution<> distribucion(0, (int) abc.size() - 1);
            int indice = distribucion(gen);
            key += abc[indice];
        }
        return key;
    }

    std::string get_env_variable_string(std::string const &key, std::string const &default_value) {
        char *c_queue = getenv(key.c_str());
        if (c_queue != nullptr) {
            return c_queue;
        } else {
            return default_value;
        }
    }

    std::set<std::string> get_env_variable_set_string(std::string const &key, std::string const &default_value) {
        std::string env_value;
        char *c_queue = getenv(key.c_str());
        if (c_queue != nullptr) {
            env_value = c_queue;
        } else {
            env_value = default_value;
        }

        // Use a stringstream to split the string
        std::stringstream ss(env_value);
        std::string token;
        std::set < std::string > result;
        while (std::getline(ss, token, ' ')) {
            // Further split token by comma
            std::stringstream inner_ss(token);
            std::string inner_token;
            while (std::getline(inner_ss, inner_token, ',')) {
                result.insert(inner_token);
            }
        }

        return result;
    }

    int get_env_variable_int(std::string const &key, int const &default_value) {
        char *c_queue = getenv(key.c_str());
        if (c_queue != nullptr) {
            try {
                return std::stoi(c_queue);
            } catch (std::invalid_argument &e) {
                return default_value;
            }
        } else {
            return default_value;
        }
    }

    bool get_env_variable_bool(const std::string &key, const bool &default_value) {
        char *c_queue = getenv(key.c_str());
        if (c_queue != nullptr && std::string(c_queue) == "true") {
            return true;
        } else if (c_queue != nullptr && std::string(c_queue) == "false") {
            return false;
        } else {
            return default_value;
        }
    }

    unsigned long long get_env_variable_long(const std::string &key, const int &default_value) {
        char *c_queue = getenv(key.c_str());
        if (c_queue != nullptr) {
            try {
                return std::stoull(c_queue);
            } catch (std::invalid_argument &e) {
                return default_value;
            }
        } else {
            return default_value;
        }
    }


    std::vector<std::string> get_env_variable_vector_string(std::string const &key, std::string const &default_value) {
        char *c_queue = getenv(key.c_str());

        if (!c_queue) {
            if (default_value.empty()) {
                return {};
            }
            c_queue = const_cast<char *>(default_value.c_str()); // Use default value if env var is not set
        }

        std::string value_str(c_queue);
        std::vector<std::string> result;
        std::istringstream value_stream(value_str);
        std::string token;

        while (std::getline(value_stream, token, ',')) {
            std::istringstream token_stream(token);
            std::string sub_token;
            while (token_stream >> sub_token) {
                result.push_back(sub_token);
                // Skip remaining whitespace in the token_stream
                token_stream >> std::ws;
            }
        }

        return result;
    }

    std::string to_string_for_json(const std::string &item) {
        return "\"" + item + "\"";
    }


    Stats::Stats() : number_of_times_queue_was_empty(0), number_of_times_queue_was_full(0) {}

    Stats::Stats(const Stats &other) {
        std::lock_guard<std::mutex> lock(stats_mutex);
        number_of_times_queue_was_empty = other.number_of_times_queue_was_empty;
        number_of_times_queue_was_full = other.number_of_times_queue_was_full;
    }

    void Stats::increment_empty() {
        std::lock_guard<std::mutex> lock(stats_mutex);
        ++number_of_times_queue_was_empty;
    }

    void Stats::increment_full() {
        std::lock_guard<std::mutex> lock(stats_mutex);
        ++number_of_times_queue_was_full;
    }

    size_t Stats::get_empty() {
        std::lock_guard<std::mutex> lock(stats_mutex);
        return number_of_times_queue_was_empty;
    }

    size_t Stats::get_full() {
        std::lock_guard<std::mutex> lock(stats_mutex);
        return number_of_times_queue_was_full;
    }

    void print_overwriteable_lines(const std::string &line1, const std::string &line2, const std::string &line3,
                                   const std::string &line4) {
        std::cout << "\033[4A";

        std::cout << "\r" << line1 << std::string(50 - line1.length(), ' ') << "\n";
        std::cout << "\r" << line2 << std::string(50 - line2.length(), ' ') << "\n";
        std::cout << "\r" << line3 << std::string(50 - line3.length(), ' ') << "\n";
        std::cout << "\r" << line4 << std::string(50 - line4.length(), ' ');

        std::cout << std::flush;
    }


}
