//
// Created by Joaquin Bejar Garcia on 6/1/24.
//



#include <common/types.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace common::types;

TEST_CASE("Inserting and finding elements in hash table", "[lock_free_hash_table]") {
    lock_free_hash_table<int, int, 10> table;
    SECTION("Newly created table should not contain elements") {
        int value;
        REQUIRE(!table.find(5, value));
    }
    SECTION("Inserting a new element should work") {
        REQUIRE(table.insert(5, 10));
        int value;
        REQUIRE(table.find(5, value));
        REQUIRE(value == 10);
    }
    SECTION("Inserting the same element should fail") {
        REQUIRE(table.insert(5, 10));
        int value;
        REQUIRE(table.find(5, value));
        REQUIRE(value == 10);
        REQUIRE(table.insert(5, 20));
        REQUIRE(table.find(5, value));
        REQUIRE(value == 20);
    }
}


TEST_CASE( "lock_free_queue", "[lock_free_queue]" ) {
    SECTION("push and pop") {
        lock_free_queue<int> queue;

        queue.push(1);
        int value;
        bool result = queue.pop(value);

        REQUIRE(result == true);
        REQUIRE(value == 1);
    }

    SECTION("push and pop multiple values") {
        lock_free_queue<int> queue;

        queue.push(1);
        queue.push(2);
        queue.push(3);

        int value;
        bool result = queue.pop(value);

        REQUIRE(result == true);
        REQUIRE(value == 1);

        result = queue.pop(value);
        REQUIRE(result == true);
        REQUIRE(value == 2);

        result = queue.pop(value);
        REQUIRE(result == true);
        REQUIRE(value == 3);
    }

    SECTION("pop from empty queue") {
        lock_free_queue<int> queue;

        int value;
        bool result = queue.pop(value);

        REQUIRE(result == false);
    }
}


TEST_CASE("lock_free_stack push and pop", "[lock_free_stack]") {
    lock_free_stack<int> stack;

    SECTION("Popping from an empty stack returns nullptr") {
        REQUIRE(stack.pop() == nullptr);
    }

    SECTION("Pushing an item onto the stack and popping it off returns the same item") {
        stack.push(42);
        auto poppedItem = stack.pop();
        REQUIRE(poppedItem != nullptr);
        REQUIRE(*poppedItem == 42);
        REQUIRE(stack.pop() == nullptr); // Stack should be empty now
    }

    SECTION("Pushing and popping multiple items maintains order") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        auto item1 = stack.pop();
        auto item2 = stack.pop();
        auto item3 = stack.pop();

        REQUIRE(item1 != nullptr);
        REQUIRE(item2 != nullptr);
        REQUIRE(item3 != nullptr);

        // This is a stack, so the last item we pushed should be the first one we pop.
        REQUIRE(*item1 == 3);
        REQUIRE(*item2 == 2);
        REQUIRE(*item3 == 1);

        REQUIRE(stack.pop() == nullptr); // Stack should be empty now
    }
}

TEST_CASE("Testing lock_free_set insertions", "[lock_free_set]") {
    lock_free_set<int> s;

    REQUIRE(s.insert(4) == true);
    REQUIRE(s.insert(2) == true);
    REQUIRE(s.insert(3) == true);

    SECTION("Duplicating an element should be true") {
        REQUIRE(s.insert(4) == true);
    }
}

TEST_CASE("Testing lock_free_set contains", "[lock_free_set]") {
    lock_free_set<int> s;

    s.insert(4);
    s.insert(2);
    s.insert(3);

    SECTION("Existing elements") {
        REQUIRE(s.contains(4) == true);
        REQUIRE(s.contains(2) == true);
        REQUIRE(s.contains(3) == true);
    }

    SECTION("Non-existing elements") {
        REQUIRE(s.contains(5) == false);
        REQUIRE(s.contains(0) == false);
        REQUIRE(s.contains(-1) == false);
    }
}
