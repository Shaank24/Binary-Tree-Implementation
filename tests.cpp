/// @file tests.cpp
/// @author Shaan Kohli
/// @date October 30, 2023

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

// This is a basic test case example with sections.
// Requires: <no other functions>
TEST_CASE("Test 0: The Null Test") 
{
    // In this section we test Scenario 1.
    SECTION("Test 0: Empty Truths")
    {
        REQUIRE(true == true);
    }

    // In this section we test Scenario 2.
    SECTION("Test 0: Empty Falsehoods")
    {
        REQUIRE(false == false);
    }
}

// tests the basic constructor and initial size
TEST_CASE("Test 1: Constructor and Size Test") {
    prqueue<int> pq;

    SECTION("Priority Queue initialized properly") {
        REQUIRE(pq.size() == 0);
    }
}

// tests enqueue and makes sure size is updated properly
TEST_CASE("Test 2: Enqueue and Size Test") {
    prqueue<int> pq;

    SECTION("Enqueue elements in priority queue") {
        pq.enqueue(10, 1);
        REQUIRE(pq.size() == 1);

        pq.enqueue(15, 2);
        REQUIRE(pq.size() == 2);
    }

    SECTION("Enqueue elements using a map") {
        map<int, vector<int> > mp;
        int n = 9;
        int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
        int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
        prqueue<int> pw;
        for (int i = 0; i < n; i++) {
            pw.enqueue(vals[i], prs[i]);
            mp[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pw.size() == 9);
    }
}

// tests if there are duplicate priorities entered in priority queue
// makes sure size is still being incremented even with duplicate priorities
TEST_CASE("Test 3: Duplicate Priority Enqueue Test") {
    prqueue<int> pq;

    SECTION("Enqueue elements with dup priorities in priority queue") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 2);
        pq.enqueue(50, 3);

        REQUIRE(pq.size() == 5);
    }
}

// tests the toString and makes sure that the output
// matches exactly by priority
TEST_CASE("Test 4: toString Test") {
    prqueue<string> pq;

    SECTION("Checking toString Output") {
        pq.enqueue("Ben", 1);
        pq.enqueue("Jen", 2);
        pq.enqueue("Sven", 2);
        pq.enqueue("Gwen", 3);

        string expected = "1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n";

        REQUIRE(pq.toString() == expected);
    }

    SECTION("Checking toString Output with duplicate priorities") {
        pq.enqueue("Raven", 1);
        pq.enqueue("Monty", 1);
        pq.enqueue("Bellamy", 1);

        string expected = "1 value: Raven\n1 value: Monty\n1 value: Bellamy\n";

        REQUIRE(pq.toString() == expected);
    }

    SECTION("Testing toString Using a Map") {
        map<int, vector<int> > mp;
        int n = 9;
        int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
        int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
        prqueue<int> pq;
        for (int i = 0; i < n; i++) {
            pq.enqueue(vals[i], prs[i]);
            mp[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pq.size() == 9);
        stringstream ss;
        for (const auto &e: mp) {
            int priority = e.first;
            vector<int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                ss << priority << " value: " << values[j] << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());
    }
}

// makes sure that clear properly updates the size
TEST_CASE("Test 5: Clear Test") {
    prqueue<int> pq;

    SECTION("Clearing priority queue") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 2);
        pq.enqueue(40, 3);

        REQUIRE(pq.size() == 4);

        pq.clear();

        REQUIRE(pq.size() == 0);
    }
}

// makes sure the equals operator function 
// correctly sets 2 prqueue to be the same
TEST_CASE("Test 6: Equals Operator Test") {
    prqueue<int> pq1, pq2;

    SECTION("Testing operator=") {
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq2 = pq1;
        REQUIRE(pq1.toString() == pq2.toString());
    }


    SECTION("Testing operator= and enqueue") {
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq2 = pq1;

        REQUIRE(pq1.toString() == pq2.toString());

        pq1.enqueue(40, 4);
        REQUIRE(pq1.toString() == "1 value: 10\n2 value: 20\n3 value: 30\n4 value: 40\n");
        REQUIRE(pq2.toString() == "1 value: 10\n2 value: 20\n3 value: 30\n");
    }

    SECTION("Testing operator= and clear") {
        pq1.clear();
        pq2 = pq1;

        REQUIRE(pq2.size() == 0);
        REQUIRE(pq1.toString() == pq2.toString());
    }
}

TEST_CASE("Test 7: Begin and Next Test") {
    prqueue<int> pq;

    SECTION("Testing with empty queue") {
        pq.begin();
        int val;
        int priority;
        REQUIRE(pq.next(val, priority) == false);
    }

    SECTION("Testing with filled queue") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 3);

        pq.begin();

        int val;
        int priority;

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 10);
        REQUIRE(priority == 1);

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 20);
        REQUIRE(priority == 2);

        REQUIRE(pq.next(val, priority) == false);
        REQUIRE(val == 30);
        REQUIRE(priority == 3);

        REQUIRE(pq.next(val, priority) == false);

    }

    SECTION("Testing with duplicate priorities") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);

        pq.begin();

        int val;
        int priority;

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 10);
        REQUIRE(priority == 1);

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 20);
        REQUIRE(priority == 1);

        REQUIRE(pq.next(val, priority) == false);
        REQUIRE(val == 30);
        REQUIRE(priority == 2);

        REQUIRE(pq.next(val, priority) == false);
    }

    SECTION("Testing with mulitple priorities") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 3);
        pq.enqueue(5, 1);
        pq.enqueue(15, 2);
        pq.enqueue(25, 3);

        pq.begin();

        int val;
        int priority;

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 10);
        REQUIRE(priority == 1);

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 5);
        REQUIRE(priority == 1);

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 20);
        REQUIRE(priority == 2);

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 15);
        REQUIRE(priority == 2);

        REQUIRE(pq.next(val, priority) == true);
        REQUIRE(val == 30);
        REQUIRE(priority == 3);

        REQUIRE(pq.next(val, priority) == false);
        REQUIRE(val == 25);
        REQUIRE(priority == 3);

        REQUIRE(pq.next(val, priority) == false);
    }
}

TEST_CASE("Test 8: Dequeue Function Test") {
    prqueue<int> pq;

    SECTION("Dequeue from empty queue") {
        REQUIRE(pq.dequeue() == int());
        REQUIRE(pq.size() == 0);
    }

    SECTION("Dequeue from queue with 1 element") {
        pq.enqueue(10, 1);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Dequeue maintains priority order") {
        pq.enqueue(10, 1);
        pq.enqueue(30, 3);
        pq.enqueue(20, 2);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == 20);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == 30);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Dequeue with multiple nodes") {
        pq.enqueue(10, 1);
        pq.enqueue(50, 3);
        pq.enqueue(20, 2);
        pq.enqueue(75, 3);
        pq.enqueue(95, 1);
        pq.enqueue(30, 2);
        pq.enqueue(25, 2);
        pq.enqueue(5, 3);
        pq.enqueue(15, 1);

        REQUIRE(pq.size() == 9);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 8);
        REQUIRE(pq.dequeue() == 95);
        REQUIRE(pq.size() == 7);
        REQUIRE(pq.dequeue() == 15);
        REQUIRE(pq.size() == 6);
        REQUIRE(pq.dequeue() == 20);
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.dequeue() == 30);
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.dequeue() == 25);
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == 50);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == 75);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == 5);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.dequeue() == 0);
    }
}

TEST_CASE("Test 9: Peek Function Test") {
    prqueue<int> pq;

    SECTION("Peek with an empty queue") {
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.peek() == 0);
    }

    SECTION("Peek with a single element") {
        pq.enqueue(10, 1);

        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 1);
    }

    SECTION("Enqueue multiple elements with different priorties") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 3);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 3);
    }

    SECTION("Dequeing elements") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 3);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 3);

        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == 20);
        REQUIRE(pq.size() == 2);

        REQUIRE(pq.dequeue() == 20);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == 30);
        REQUIRE(pq.size() == 1);
    }

    SECTION("Handles duplicate priorities") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 2);
        pq.enqueue(40, 1);

        REQUIRE(pq.size() == 4);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 4);

        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 40);
        REQUIRE(pq.size() == 3);   
    }

    SECTION("Copy Assingment operator with Peek") {
        prqueue<int> pq2;
        pq2.enqueue(10, 1);

        pq = pq2;

        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.peek() == 0);
        REQUIRE(pq.size() == 0);
    }
}

TEST_CASE("Test 10: Operator== Test") {
    prqueue<int> pq1, pq2;

    SECTION("Comparing 2 empty prqueues") {
        REQUIRE(pq1 == pq2);
    }

    SECTION("Comparing empty prqueue with non-empty prqueue") {
        pq1.enqueue(10, 1);
        REQUIRE((pq1 == pq2) == false);
    }

    SECTION("Comparing 2 prqueues with same elements") {
        pq1.enqueue(10, 1);
        pq2.enqueue(10, 1);
        REQUIRE(pq1 == pq2);
    }

    SECTION("Comparing 2 prqueues with different elements") {
        pq1.enqueue(10, 1);
        pq2.enqueue(20, 2);
        REQUIRE((pq1 == pq2) == false);
    }

    SECTION("Comparing 2 prqueues with same elements but different order") {
        pq1.enqueue(5, 1);
        pq1.enqueue(10, 2);

        pq2.enqueue(10, 2);
        pq2.enqueue(5, 1);
        REQUIRE((pq1 == pq2) == false);
    }

    SECTION("Comparing 2 prqueues with multiple same elements") {
        pq1.enqueue(5, 1);
        pq2.enqueue(5, 1);
        pq1.enqueue(15, 2);
        pq2.enqueue(15, 2);
        pq1.enqueue(25, 1);
        pq2.enqueue(25, 1);
        pq1.enqueue(1, 3);
        pq2.enqueue(1, 3);
        pq1.enqueue(45, 3);
        pq2.enqueue(45, 3);
        REQUIRE(pq1 == pq2);
    }

    SECTION("Comparing 2 prqueues with same elements but different priority") {
        pq1.enqueue(5, 1);
        pq2.enqueue(5, 1);
        pq1.enqueue(15, 2);
        pq2.enqueue(15, 2);
        pq1.enqueue(25, 1);
        pq2.enqueue(25, 2);
        pq1.enqueue(1, 2);
        pq2.enqueue(1, 3);
        pq1.enqueue(45, 1);
        pq2.enqueue(45, 3);
        REQUIRE((pq1 == pq2) == false);
    }

    SECTION("Comparing 2 prqueues where 1 has more elements") {
        pq1.enqueue(5, 1);
        pq2.enqueue(5, 1);
        pq1.enqueue(15, 2);
        pq2.enqueue(15, 2);
        pq1.enqueue(25, 1);
        pq2.enqueue(25, 1);
        pq1.enqueue(1, 3);
        pq2.enqueue(1, 3);
        pq1.enqueue(45, 3);
        REQUIRE((pq1 == pq2) == false);
    }

    SECTION("Comparing prqueue with itself") {
        pq1.enqueue(10, 1);
        REQUIRE(pq1 == pq1);
    }

    SECTION("Comparing 2 prqueues with duplicate elements in 1") {
        pq1.enqueue(10, 1);
        pq1.enqueue(10, 1);
        pq2.enqueue(10, 1);

        REQUIRE((pq1 == pq2) == false);
    }

    SECTION("Comparing 2 prqueues after dequeueing elements") {
        pq1.enqueue(5, 1);
        pq2.enqueue(5, 1);
        REQUIRE(pq1 == pq2);
        pq1.enqueue(15, 2);
        pq2.enqueue(15, 2);
        REQUIRE(pq1 == pq2);
        pq1.dequeue();
        REQUIRE((pq1 == pq2) == false);
        pq2.dequeue();
        REQUIRE(pq1 == pq2);
        pq1.enqueue(3, 2);
        REQUIRE((pq1 == pq2) == false);
        pq2.enqueue(3, 2);
        REQUIRE(pq1 == pq2);
    }
}

TEST_CASE("MULTIPLE FUNCTION CALLS TEST") {
    prqueue<int> pq1;
    prqueue<int> pq2;
    prqueue<int> pq3;

    SECTION("Part 1") {
        REQUIRE(pq1.size() == 0);
        pq1.enqueue(5, 1);
        pq2.enqueue(5, 1);
        pq3.enqueue(5, 1);
        pq1.enqueue(15, 2);
        pq2.enqueue(15, 2);
        pq3.enqueue(15, 2);

        REQUIRE(pq1.size() == 2);
        REQUIRE(pq2.size() == 2);
        REQUIRE(pq3.size() == 2);
        REQUIRE(pq1 == pq2);
        REQUIRE(pq2 == pq3);
        REQUIRE(pq1 == pq3);

        REQUIRE(pq1.peek() == 5);
        pq1.dequeue();
        REQUIRE(pq1.peek() == 15);
        REQUIRE(pq1.size() == 1);
    }

    SECTION("Part 2") {
        pq1.enqueue(5, 1);
        pq1.enqueue(15, 1);
        REQUIRE(pq2.size() == 0);

        pq2 = pq1;
        REQUIRE(pq1 == pq2);
        REQUIRE(pq2.size() == 2);

        pq1.clear();
        REQUIRE(pq1.size() == 0);
        REQUIRE((pq1 == pq2) == false);

        pq2.clear();
        REQUIRE(pq2.size() == 0);
        REQUIRE((pq1 == pq2) == true);
    }

    SECTION("Part 3") {
        
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(5, 3);

        pq2 = pq1;
        pq3 = pq2;

        string pq1String = pq1.toString();
        string pq2String = pq2.toString();
        string pq3String = pq3.toString();

        REQUIRE(pq1String == "1 value: 10\n2 value: 20\n3 value: 5\n");
        REQUIRE(pq2String == "1 value: 10\n2 value: 20\n3 value: 5\n");
        REQUIRE(pq3String == "1 value: 10\n2 value: 20\n3 value: 5\n");
        REQUIRE(pq1.peek() == 10);
        REQUIRE(pq2.peek() == 10);
        REQUIRE(pq3.peek() == 10);

        pq1.dequeue();
        REQUIRE(pq1.peek() == 20);
        pq1.dequeue();
        REQUIRE(pq1.peek() == 5);
        pq1.dequeue();
        REQUIRE(pq1.peek() == 0);

        pq1.clear();
        pq2.clear();
        pq3.clear();

        REQUIRE(pq1.size() == 0);
        REQUIRE(pq2.size() == 0);
        REQUIRE(pq3.size() == 0);
        REQUIRE(pq1 == pq2);
        REQUIRE(pq2 == pq3);
        REQUIRE(pq1 == pq3);
    }
}
