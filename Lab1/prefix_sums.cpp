#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <vector>

// Function to check if the prefix sums never go below zero
bool non_neg_prefix_sum(const std::vector<int>& arr) {
    int prefix_sum = 0;
    for (int num : arr) {
        prefix_sum += num;
        if (prefix_sum < 0) {
            return false; // Prefix sum went below zero
        }
    }
    return true; // All prefix sums are non-negative
}

// Function to check if the prefix sums never go above zero
bool non_pos_prefix_sum(const std::vector<int>& arr) {
    int prefix_sum = 0;
    for (int num : arr) {
        prefix_sum += num;
        if (prefix_sum > 0) {
            return false; // Prefix sum went above zero
        }
    }
    return true; // All prefix sums are non-positive
}

// Test cases
TEST_CASE("Testing non_neg_prefix_sum") {
    std::vector<int> test1 = {1, -1, 1, -1};
    std::vector<int> test2 = {1, -1, -1, 1};

    CHECK(non_neg_prefix_sum(test1) == true);
    CHECK(non_neg_prefix_sum(test2) == false);
}

TEST_CASE("Testing non_pos_prefix_sum") {
    std::vector<int> test3 = {-1, 1, -1, 1};
    std::vector<int> test4 = {-1, -1, 1, 1};

    CHECK(non_pos_prefix_sum(test3) == true);
    CHECK(non_pos_prefix_sum(test4) == true);
}

