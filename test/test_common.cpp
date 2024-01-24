//
// Created by Joaquin Bejar Garcia on 19/10/23.
//

#include <common/common.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace common;
// ---------------------------------------------------------------------------------------------------
TEST_CASE("Declare config", "[Common]") {

    REQUIRE(true);
}

TEST_CASE("to_upper works correctly", "[to_upper]") {
    using common::to_upper;

    SECTION("Mixed case") {
        REQUIRE(to_upper("HeLLo") == "HELLO");
    }

    SECTION("All lower") {
        REQUIRE(to_upper("world") == "WORLD");
    }

    SECTION("All upper") {
        REQUIRE(to_upper("WORLD") == "WORLD");
    }

    SECTION("Empty string") {
        REQUIRE(to_upper("").empty());
    }
}

TEST_CASE("to_lower works correctly", "[to_lower]") {
    using common::to_lower;

    SECTION("Mixed case") {
        REQUIRE(to_lower("HeLLo") == "hello");
    }

    SECTION("All lower") {
        REQUIRE(to_lower("world") == "world");
    }

    SECTION("All upper") {
        REQUIRE(to_lower("WORLD") == "world");
    }

    SECTION("Empty string") {
        REQUIRE(to_lower("").empty());
    }
}

TEST_CASE("to_hash works correctly", "[to_hash]") {
    using common::to_hash;

    SECTION("Non-empty strings") {
        REQUIRE(to_hash("hello") != to_hash("world"));
        REQUIRE(to_hash("hello") == to_hash("hello"));
    }

    SECTION("Empty string") {
        REQUIRE(to_hash("") == std::to_string(std::hash<std::string>{}("")));
    }
}

TEST_CASE("get_env_variable_set_string works correctly", "[get_env_variable_set_string]") {
    using common::get_env_variable_set_string;

    SECTION("Environment variable exists") {
        setenv("MY_TEST_ENV", "value1,value2 value3,value4", 1);
        auto result = get_env_variable_set_string("MY_TEST_ENV", "default_value");
        REQUIRE(result.size() == 4);
        REQUIRE(result.find("value1") != result.end());
        REQUIRE(result.find("value2") != result.end());
        REQUIRE(result.find("value3") != result.end());
        REQUIRE(result.find("value4") != result.end());
    }

    SECTION("Environment variable does not exist") {
        unsetenv("MY_TEST_ENV");
        auto result = get_env_variable_set_string("MY_TEST_ENV", "default_value");
        REQUIRE(result.size() == 1);
        REQUIRE(result.find("default_value") != result.end());
    }

    SECTION("Environment variable is empty") {
        setenv("MY_TEST_ENV", "", 1);
        auto result = get_env_variable_set_string("MY_TEST_ENV", "default_value");
        REQUIRE(result.empty());
    }

    SECTION("Default value is used") {
        unsetenv("MY_TEST_ENV");
        auto result = get_env_variable_set_string("MY_TEST_ENV", "default1,default2");
        REQUIRE(result.size() == 2);
        REQUIRE(result.find("default1") != result.end());
        REQUIRE(result.find("default2") != result.end());
    }
}

TEST_CASE("get_env_variable_int works correctly", "[get_env_variable_int]") {
    using common::get_env_variable_int;

    SECTION("Environment variable exists and is a valid integer") {
        setenv("MY_INT_ENV", "42", 1);
        int result = get_env_variable_int("MY_INT_ENV", 0);
        REQUIRE(result == 42);
    }

    SECTION("Environment variable exists but is not an integer") {
        setenv("MY_INT_ENV", "not_an_int", 1);
        int result = get_env_variable_int("MY_INT_ENV", 0);
        REQUIRE(result == 0);
    }

    SECTION("Environment variable does not exist") {
        unsetenv("MY_INT_ENV");
        int result = get_env_variable_int("MY_INT_ENV", 0);
        REQUIRE(result == 0);
    }

    SECTION("Environment variable is empty") {
        setenv("MY_INT_ENV", "", 1);
        int result = get_env_variable_int("MY_INT_ENV", 0);
        REQUIRE(result == 0);
    }

    SECTION("Default value is used") {
        unsetenv("MY_INT_ENV");
        int result = get_env_variable_int("MY_INT_ENV", 99);
        REQUIRE(result == 99);
    }
}

TEST_CASE("get_env_variable_bool works correctly", "[get_env_variable_bool]") {
    using common::get_env_variable_bool;

    SECTION("Environment variable exists and is 'true'") {
        setenv("MY_BOOL_ENV", "true", 1);
        bool result = get_env_variable_bool("MY_BOOL_ENV", false);
        REQUIRE(result == true);
    }

    SECTION("Environment variable exists and is 'false'") {
        setenv("MY_BOOL_ENV", "false", 1);
        bool result = get_env_variable_bool("MY_BOOL_ENV", true);
        REQUIRE(result == false);
    }

    SECTION("Environment variable exists but is neither 'true' nor 'false'") {
        setenv("MY_BOOL_ENV", "neither", 1);
        bool result = get_env_variable_bool("MY_BOOL_ENV", true);
        REQUIRE(result == true);
    }

    SECTION("Environment variable does not exist") {
        unsetenv("MY_BOOL_ENV");
        bool result = get_env_variable_bool("MY_BOOL_ENV", true);
        REQUIRE(result == true);
    }

    SECTION("Environment variable is empty") {
        setenv("MY_BOOL_ENV", "", 1);
        bool result = get_env_variable_bool("MY_BOOL_ENV", true);
        REQUIRE(result == true);
    }

    SECTION("Default value is used") {
        unsetenv("MY_BOOL_ENV");
        bool result = get_env_variable_bool("MY_BOOL_ENV", false);
        REQUIRE(result == false);
    }
}

TEST_CASE("get_env_variable_long works correctly", "[get_env_variable_long]") {
    using common::get_env_variable_long;

    SECTION("Environment variable exists and is a valid unsigned long long") {
        setenv("MY_LONG_ENV", "18446744073709551615", 1); // Max value for unsigned long long
        auto result = get_env_variable_long("MY_LONG_ENV", 0);
        REQUIRE(result == 18446744073709551615ULL);
    }

    SECTION("Environment variable exists but is not an unsigned long long") {
        setenv("MY_LONG_ENV", "not_a_long", 1);
        auto result = get_env_variable_long("MY_LONG_ENV", 0);
        REQUIRE(result == 0);
    }

    SECTION("Environment variable does not exist") {
        unsetenv("MY_LONG_ENV");
        auto result = get_env_variable_long("MY_LONG_ENV", 0);
        REQUIRE(result == 0);
    }

    SECTION("Environment variable is empty") {
        setenv("MY_LONG_ENV", "", 1);
        auto result = get_env_variable_long("MY_LONG_ENV", 0);
        REQUIRE(result == 0);
    }

    SECTION("Default value is used") {
        unsetenv("MY_LONG_ENV");
        auto result = get_env_variable_long("MY_LONG_ENV", 99);
        REQUIRE(result == 99);
    }
}

TEST_CASE("get_env_variable_string works correctly", "[get_env_variable_string]") {
    using common::get_env_variable_string;

    SECTION("Environment variable exists") {
        setenv("MY_STRING_ENV", "my_value", 1);
        auto result = get_env_variable_string("MY_STRING_ENV", "default_value");
        REQUIRE(result == "my_value");
    }

    SECTION("Environment variable does not exist") {
        unsetenv("MY_STRING_ENV");
        auto result = get_env_variable_string("MY_STRING_ENV", "default_value");
        REQUIRE(result == "default_value");
    }

    SECTION("Environment variable is empty") {
        setenv("MY_STRING_ENV", "", 1);
        auto result = get_env_variable_string("MY_STRING_ENV", "default_value");
        REQUIRE(result.empty());
    }

    SECTION("Default value is used") {
        unsetenv("MY_STRING_ENV");
        auto result = get_env_variable_string("MY_STRING_ENV", "default_value");
        REQUIRE(result == "default_value");
    }
}

TEST_CASE("key_generator works correctly", "[key_generator]") {
    using common::key_generator;

    SECTION("Generated key length is correct") {
        auto generated_key = key_generator();
        REQUIRE(generated_key.length() == 23);  // 20 characters + 3 underscores
    }

    SECTION("Generated key contains underscores at correct positions") {
        auto generated_key = key_generator();
        REQUIRE(generated_key[5] == '_');
        REQUIRE(generated_key[11] == '_');
        REQUIRE(generated_key[17] == '_');
    }

    SECTION("Generated keys are unique") {
        auto generated_key1 = key_generator();
        auto generated_key2 = key_generator();
        REQUIRE(generated_key1 != generated_key2);
    }

    SECTION("Generated keys contain only lowercase alphabets and underscores") {
        auto generated_key = key_generator();
        for (char c: generated_key) {
            REQUIRE(((c >= 'a' && c <= 'z') || c == '_'));
        }
    }
}

TEST_CASE("setTojson works correctly", "[setTojson]") {
    using common::set_to_json;

    SECTION("Empty set") {
        std::set<std::string> s;
        auto json = set_to_json(s);
        REQUIRE(json == "[]");
    }

    SECTION("Single item set") {
        std::set<std::string> s = {"item1"};
        auto json = set_to_json(s);
        REQUIRE(json == "[\"item1\"]");
    }

    SECTION("Multiple items set") {
        std::set<std::string> s = {"item1", "item2", "item3"};
        auto json = set_to_json(s);
        REQUIRE(json == "[\"item1\",\"item2\",\"item3\"]");
    }

    SECTION("Set with numeric items") {
        std::set<int> s = {1, 2, 3};
        auto json = set_to_json(s);
        REQUIRE(json == "[1,2,3]");
    }

    SECTION("Set with long items") {
        std::set<long> s = {1, 2, 3};
        auto json = set_to_json(s);
        REQUIRE(json == "[1,2,3]");
    }

    SECTION("Set with long items") {
        std::set<float> s = {1.1, 2, 3.1};
        auto json = set_to_json(s);
        REQUIRE(json == "[1.100000,2.000000,3.100000]");
    }
}

TEST_CASE("to_string_for_json function tests", "[to_string_for_json]") {
    using common::to_string_for_json;

    SECTION("Converts integers to string") {
        int val = 42;
        REQUIRE(to_string_for_json(val) == "42");
    }

    SECTION("Converts floats to string") {
        float val = 42.42;
        REQUIRE_THAT(std::stof(to_string_for_json(val)), Catch::Matchers::WithinAbs(42.42, 0.002));
    }

    SECTION("Converts doubles to string") {
        double val = 42.42;
        REQUIRE_THAT(std::stof(to_string_for_json(val)), Catch::Matchers::WithinAbs(42.42, 0.0001));
    }
}

TEST_CASE("join_sets function tests", "[join_sets]") {
    using common::join_sets;

    SECTION("Join sets of integers") {
        std::set<int> set1 = {1, 2, 3};
        std::set<int> set2 = {3, 4, 5};
        std::set<int> result = join_sets(set1, set2);
        std::set<int> expected = {1, 2, 3, 4, 5};
        REQUIRE(result == expected);
    }

    SECTION("Join sets of strings") {
        std::set<std::string> set1 = {"a", "b", "c"};
        std::set<std::string> set2 = {"c", "d", "e"};
        std::set<std::string> result = join_sets(set1, set2);
        std::set<std::string> expected = {"a", "b", "c", "d", "e"};
        REQUIRE(result == expected);
    }

    SECTION("Join empty sets") {
        std::set<int> set1 = {};
        std::set<int> set2 = {};
        std::set<int> result = join_sets(set1, set2);
        std::set<int> expected = {};
        REQUIRE(result == expected);
    }

}

TEST_CASE("vector_to_set function tests", "[vector_to_set]") {
    using common::vector_to_set;

    SECTION("Convert vector of integers to set") {
        std::vector<int> vec = {1, 2, 3, 3, 4, 4, 5};
        std::set<int> result = vector_to_set(vec);
        std::set<int> expected = {1, 2, 3, 4, 5};
        REQUIRE(result == expected);
    }

    SECTION("Convert vector of strings to set") {
        std::vector<std::string> vec = {"a", "b", "c", "c", "d"};
        std::set<std::string> result = vector_to_set(vec);
        std::set<std::string> expected = {"a", "b", "c", "d"};
        REQUIRE(result == expected);
    }

    SECTION("Convert empty vector to empty set") {
        std::vector<int> vec = {};
        std::set<int> result = vector_to_set(vec);
        std::set<int> expected = {};
        REQUIRE(result == expected);
    }

}

TEST_CASE("Testing ThreadQueue functionality", "[queue]") {
    common::ThreadQueue<int> intQueue;
    common::ThreadQueue<std::string> stringQueue;

    SECTION("Testing enqueue method") {
        REQUIRE(intQueue.enqueue(42) == true);
        REQUIRE(stringQueue.enqueue("hello") == true);
    }

    SECTION("Testing dequeue method") {
        int intItem;
        std::string stringItem;

        REQUIRE(intQueue.enqueue(42) == true);
        REQUIRE(intQueue.dequeue(intItem) == true);
        REQUIRE(intItem == 42);

        REQUIRE(stringQueue.enqueue("hello") == true);
        REQUIRE(stringQueue.dequeue(stringItem) == true);
        REQUIRE(stringItem == "hello");

        REQUIRE(intQueue.dequeue(intItem) == false);  // Queue is empty
        REQUIRE(stringQueue.dequeue(stringItem) == false);  // Queue is empty
    }

    SECTION("Testing dequeue_blocking method") {
        int intItem;
        std::string stringItem;

        std::thread producer1([&intQueue]() { intQueue.enqueue(42); });
        std::thread consumer1([&intQueue, &intItem]() { REQUIRE(intQueue.dequeue_blocking(intItem) == true); });
        producer1.join();
        consumer1.join();
        REQUIRE(intItem == 42);

        std::thread producer2([&stringQueue]() { stringQueue.enqueue("hello"); });
        std::thread consumer2(
                [&stringQueue, &stringItem]() { REQUIRE(stringQueue.dequeue_blocking(stringItem) == true); });
        producer2.join();
        consumer2.join();
        REQUIRE(stringItem == "hello");
    }
}

TEST_CASE("Testing ThreadQueueWithMaxSize functionality", "[queue]") {
    common::ThreadQueueWithMaxSize<int> intQueue(100);
    common::ThreadQueueWithMaxSize<std::string> stringQueue(100);

    SECTION("Testing enqueue method") {
        REQUIRE(intQueue.enqueue(42) == true);
        REQUIRE(stringQueue.enqueue("hello") == true);
    }

    SECTION("Testing dequeue method") {
        int intItem;
        std::string stringItem;

        REQUIRE(intQueue.enqueue(42) == true);
        REQUIRE(intQueue.dequeue(intItem) == true);
        REQUIRE(intItem == 42);

        REQUIRE(stringQueue.enqueue("hello") == true);
        REQUIRE(stringQueue.dequeue(stringItem) == true);
        REQUIRE(stringItem == "hello");

        REQUIRE(intQueue.dequeue(intItem) == false);  // Queue is empty
        REQUIRE(stringQueue.dequeue(stringItem) == false);  // Queue is empty
    }

    SECTION("Testing dequeue_blocking method") {
        int intItem;
        std::string stringItem;

        std::thread producer1([&intQueue]() { intQueue.enqueue(42); });
        std::thread consumer1([&intQueue, &intItem]() { REQUIRE(intQueue.dequeue_blocking(intItem) == true); });
        producer1.join();
        consumer1.join();
        REQUIRE(intItem == 42);

        std::thread producer2([&stringQueue]() { stringQueue.enqueue("hello"); });
        std::thread consumer2(
                [&stringQueue, &stringItem]() { REQUIRE(stringQueue.dequeue_blocking(stringItem) == true); });
        producer2.join();
        consumer2.join();
        REQUIRE(stringItem == "hello");
    }

    SECTION("Testing dequeue_blocking method with max size Int") {
        int intItem;


        std::thread producer1([&intQueue]() {
            for (int i = 0; i < 1000; i++) {
                intQueue.enqueue(i);
            }
        });
        std::thread consumer1([&intQueue, &intItem]() {
            for (int i = 0; i < 1000; i++) {
                REQUIRE(intQueue.dequeue_blocking(intItem) == true);
            }
        });
        producer1.join();
        consumer1.join();

        common::Stats stats = intQueue.get_stats();
        REQUIRE(stats.get_empty() > 0);
        REQUIRE(stats.get_full() > 0);

    }

    SECTION("Testing dequeue_blocking method with max size String") {
        std::string stringItem;
        std::thread producer2([&stringQueue]() {
            for (int i = 0; i < 1000; i++) {
                stringQueue.enqueue("hello_" + std::to_string(i));
            }
        });
        std::thread consumer2([&stringQueue, &stringItem]() {
            for (int i = 0; i < 1000; i++) {
                REQUIRE(stringQueue.dequeue_blocking(stringItem) == true);
            }
        });
        producer2.join();
        consumer2.join();

        common::Stats stats = stringQueue.get_stats();
        REQUIRE(stats.get_empty() > 0);
        REQUIRE(stats.get_full() > 0);
    }
}

TEST_CASE("Shuffle vector") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto originalVec = vec;

    SECTION("Size remains constant after shuffling") {
        shuffle_vector(vec);
        REQUIRE(vec.size() == originalVec.size());
    }
}

TEST_CASE("Extract elements from vector string") {
    std::vector<std::string> vec = {"a", "b", "c", "d", "e"};
    int numElements = 3;
    auto originalSize = vec.size();

    SECTION("Extract correct number of elements") {
        auto extracted = extract_elements_from_vector(vec, numElements);
        REQUIRE(extracted.size() == numElements);
    }

    SECTION("Original vector is reduced") {
        extract_elements_from_vector(vec, numElements);
        REQUIRE(vec.size() == originalSize - numElements);
    }

    SECTION("Extracted elements are the last ones") {
        auto extracted = extract_elements_from_vector(vec, numElements);
        REQUIRE(extracted == std::vector<std::string>({"c", "d", "e"}));
    }

    SECTION("Handle more elements than size") {
        auto extracted = extract_elements_from_vector(vec, 10);
        REQUIRE(extracted.size() == originalSize);
    }

    SECTION("Handle negative number of elements") {
        auto extracted = extract_elements_from_vector(vec, -3);
        REQUIRE(extracted.empty());
    }
}

TEST_CASE("Extract elements from vector size_t") {
    std::vector<size_t> vec = {1, 2, 3, 4, 5};
    int numElements = 3;
    auto originalSize = vec.size();

    SECTION("Extract correct number of elements") {
        auto extracted = extract_elements_from_vector(vec, numElements);
        REQUIRE(extracted.size() == numElements);
    }

    SECTION("Original vector is reduced") {
        extract_elements_from_vector(vec, numElements);
        REQUIRE(vec.size() == originalSize - numElements);
    }

    SECTION("Extracted elements are the last ones") {
        auto extracted = extract_elements_from_vector(vec, numElements);
        REQUIRE(extracted == std::vector<size_t>({3, 4, 5}));
    }

    SECTION("Handle more elements than size") {
        auto extracted = extract_elements_from_vector(vec, 10);
        REQUIRE(extracted.size() == originalSize);
    }

    SECTION("Handle negative number of elements") {
        auto extracted = extract_elements_from_vector(vec, -3);
        REQUIRE(extracted.empty());
    }
}

TEST_CASE("Get vector fron env variable") {

    SECTION("single value") {
        setenv("MY_ENV", "value1", 1);
        std::vector<std::string> result = get_env_variable_vector_string("MY_ENV", "default_value");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == "value1");
    }

    SECTION("Values with comas") {
        setenv("MY_ENV_COMMAS", "value1,value2,value3", 1);
        std::vector<std::string> result = get_env_variable_vector_string("MY_ENV_COMMAS", "default_value");
        REQUIRE(result.size() == 3);
        REQUIRE(result[0] == "value1");
        REQUIRE(result[1] == "value2");
        REQUIRE(result[2] == "value3");
    }

    SECTION("Values with spaces") {
        setenv("MY_ENV_SPACES", "value1 value2 value3", 1);
        std::vector<std::string> result = get_env_variable_vector_string("MY_ENV_SPACES", "default_value");
        REQUIRE(result.size() == 3);
        REQUIRE(result[0] == "value1");
        REQUIRE(result[1] == "value2");
        REQUIRE(result[2] == "value3");
    }

    SECTION("Values mix 1") {
        setenv("MY_ENV_MIX1", "value1, value2,value3", 1);
        std::vector<std::string> result = get_env_variable_vector_string("MY_ENV_MIX1", "default_value");
        REQUIRE(result.size() == 3);
        REQUIRE(result[0] == "value1");
        REQUIRE(result[1] == "value2");
        REQUIRE(result[2] == "value3");
    }

    SECTION("Values mix 2") {
        setenv("MY_ENV_MIX2", "value1  value2 value3    value4", 1);
        std::vector<std::string> result = get_env_variable_vector_string("MY_ENV_MIX2", "default_value");
        REQUIRE(result.size() == 4);
        REQUIRE(result[0] == "value1");
        REQUIRE(result[1] == "value2");
        REQUIRE(result[2] == "value3");
        REQUIRE(result[3] == "value4");
    }

    SECTION("Values mix 3") {
        setenv("MY_ENV_MIX3", "value1  ,value2, value3,    value4", 1);
        std::vector<std::string> result = get_env_variable_vector_string("MY_ENV_MIX3", "default_value");
        REQUIRE(result.size() == 4);
        REQUIRE(result[0] == "value1");
        REQUIRE(result[1] == "value2");
        REQUIRE(result[2] == "value3");
        REQUIRE(result[3] == "value4");
    }

    SECTION("Default") {
        std::vector<std::string> result = get_env_variable_vector_string("DEFAULT_VALUE", "default_value");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == "default_value");
    }

}