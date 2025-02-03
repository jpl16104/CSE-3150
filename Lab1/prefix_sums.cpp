#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <iostream>
using namespace std;

bool checkPrefixNonNegative(const int data[], int length) {
    int runningSum = 0;             // Initialize the running (prefix) sum to 0.
    for (int i = 0; i < length; ++i) {  // Loop through each element in the array.
        runningSum += data[i];         // Add the current element to the running sum.
        if (runningSum < 0) {          // If at any point the running sum is negative...
            return false;              // ...return false immediately.
        }
    }
    return true;                     // All prefix sums are non-negative.
}

bool checkPrefixNonPositive(const int data[], int length) {
    int runningSum = 0;             // Initialize the running (prefix) sum to 0.
    for (int i = 0; i < length; ++i) {  // Loop through each element in the array.
        runningSum += data[i];         // Add the current element to the running sum.
        if (runningSum > 0) {          // If the running sum becomes positive...
            return false;              // ...return false immediately.
        }
    }
    return true;                     // All prefix sums are non-positive.
}

TEST_CASE("Alternating array starting with +1") {
    int arr[] = {1, -1, 1, -1};  // Define a test array.
    CHECK(checkPrefixNonNegative(arr, 4) == true);
    CHECK(checkPrefixNonPositive(arr, 4) == false);
}

// Test case: Array that goes negative: {1, -1, -1, 1}
// Expected prefix sums: 0, 1, 0, -1, 0.
TEST_CASE("Array that goes negative") {
    int arr[] = {1, -1, -1, 1};  // Define a test array.
    CHECK(checkPrefixNonNegative(arr, 4) == false);
    CHECK(checkPrefixNonPositive(arr, 4) == false); 
}

// Test case: Array valid for non-positive prefix: {-1, 1, -1, 1}
// Expected prefix sums: 0, -1, 0, -1, 0.
TEST_CASE("Array valid for non-positive prefix") {
    int arr[] = {-1, 1, -1, 1};  // Define a test array.
    CHECK(checkPrefixNonNegative(arr, 4) == false);
    CHECK(checkPrefixNonPositive(arr, 4) == true);
}

// Test case: Array with all -1 values: {-1, -1, -1, -1}
// Expected prefix sums: 0, -1, -2, -3, -4.
TEST_CASE("Array with all -1 values") {
    int arr[] = {-1, -1, -1, -1};  // Define a test array.
    CHECK(checkPrefixNonNegative(arr, 4) == false);
    CHECK(checkPrefixNonPositive(arr, 4) == true);
}

// Test case: Array with all +1 values: {1, 1, 1, 1}
// Expected prefix sums: 0, 1, 2, 3, 4.
TEST_CASE("Array with all +1 values") {
    int arr[] = {1, 1, 1, 1};  // Define a test array.
    CHECK(checkPrefixNonNegative(arr, 4) == true); 
    CHECK(checkPrefixNonPositive(arr, 4) == false);
}
// Main Function
int main(int argc, char** argv) {
    // Create a doctest context to manage test execution.
    doctest::Context context;

    // Apply command-line arguments to the context (enables doctest options).
    context.applyCommandLine(argc, argv);

    // Run all registered tests; the result is the number of failed tests.
    int testResult = context.run();

    // If doctest indicates that we should exit (for example, if --exit was used),
    // then exit now with the test result.
    if (context.shouldExit()) {
        return testResult;
    }
    // Interactive Portion: Prompt the user for input and process it.

    int arraySize;  // Variable to store the number of elements in the array.
    cout << "\nEnter the number of elements for the array: ";
    cin >> arraySize;  // Read the array size from the user.

    // Validate that the array size is a positive number.
    if (arraySize <= 0) {
        cout << "Error: Array size must be a positive integer." << endl;
        return 1;  // Exit with an error code.
    }

    // Dynamically allocate an array to store the user's input numbers.
    int* arr = new int[arraySize];

    // Prompt the user to enter the array elements (each should be either +1 or -1).
    cout << "Enter " << arraySize << " numbers (each should be either +1 or -1):" << endl;
    for (int i = 0; i < arraySize; ++i) {
        cin >> arr[i];  // Read each number into the array.
    }

    // Use the prefix sum functions to check the conditions.
    bool nonNeg = checkPrefixNonNegative(arr, arraySize);
    bool nonPos = checkPrefixNonPositive(arr, arraySize);

    // Display the results to the user.
    cout << "\nResults:" << endl;
    cout << "Prefix sums never go below zero: " << (nonNeg ? "true" : "false") << endl;
    cout << "Prefix sums never go above zero: " << (nonPos ? "true" : "false") << endl;

    // Free the dynamically allocated memory.
    delete[] arr;
    return testResult;
}