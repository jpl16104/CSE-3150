#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void fisherYatesShuffle(std::vector<int>& list) {
    for (int i = list.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(list[i], list[j]);
    }
}

bool isWellBalanced(const std::vector<int>& list) {
    int sum = 0;
    bool hasNegative = false, hasPositive = false;
    
    for (int i = 0; i < list.size(); ++i) {
        sum += list[i];
        if (sum < 0) hasNegative = true;
        if (sum > 0) hasPositive = true;
        
        // If both negative and positive prefix sums are found, discard the list
        if (hasNegative && hasPositive) return false;
    }
    return true;
}

double proportionOfWellBalanced(int n, int totalRuns) {
    int validRuns = 0;
    
    for (int i = 0; i < totalRuns; ++i) {
        std::vector<int> list(2 * n, 0);
        std::fill(list.begin(), list.begin() + n, 1); // First n elements are 1
        std::fill(list.begin() + n, list.end(), -1); // Last n elements are -1
        
        fisherYatesShuffle(list); // Shuffle the list
        
        if (isWellBalanced(list)) {
            ++validRuns;
        }
    }
    
    return static_cast<double>(validRuns) / totalRuns;
}

// Unit tests using Doctest
TEST_CASE("Test well-balanced list validation") {
    std::vector<int> validList = {1, -1, 1, -1};
    std::vector<int> invalidList = {1, -1, -1, 1};

    CHECK(isWellBalanced(validList) == true);  // Well-balanced
    CHECK(isWellBalanced(invalidList) == false);  // Not well-balanced
}

TEST_CASE("Test Fisher-Yates shuffle randomness") {
    std::vector<int> list = {1, 1, -1, -1};
    std::vector<int> originalList = list;

    fisherYatesShuffle(list);
    
    // The list should have been shuffled (not equal to the original)
    CHECK(list != originalList);
}

TEST_CASE("Test proportion calculation for large n") {
    int n = 5;
    int totalRuns = 1000;
    
    double proportion = proportionOfWellBalanced(n, totalRuns);
    
    // The proportion should be between 0 and 1
    CHECK(proportion >= 0.0);
    CHECK(proportion <= 1.0);
}

void runWithUserInput() {
    int n;
    std::cout << "Enter the number of pairs of matching symbols (n): ";
    std::cin >> n;

    int totalRuns = 10000;
    double proportion = proportionOfWellBalanced(n, totalRuns);

    std::cout << "Total runs: " << totalRuns << std::endl;
    std::cout << "Proportion of well-balanced lists: " << proportion << std::endl;
}

TEST_CASE("Test with user input for proportion") {
    runWithUserInput();
}
