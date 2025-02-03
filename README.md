# Jean Lara Lab Week 1: Prefix Sums Checker

This program validates whether the prefix sums of an array (composed solely of +1 and -1 values) meet two conditions:
- **Non-negative:** The cumulative (prefix) sum never falls below 0.
- **Non-positive:** The cumulative (prefix) sum never rises above 0.

The program includes automated tests using the [doctest](https://github.com/onqtam/doctest) framework and then enters an interactive mode.

---

## Requirements

- A C++ compiler (e.g., g++)
- The header-only [doctest](https://github.com/onqtam/doctest) library  
  (Ensure that `doctest.h` is in the same directory as your source code or in your include path.)

---

## How to Compile

1. Open a terminal in the directory containing `prefix_sums.cpp`.
2. Compile the program using:
   ```bash
   g++ -std=c++17 prefix_sums.cpp -o prefix_sums
   ```
---

## How to Run and Test

1. Run the compiled program by executing:
   ```bash
   ./prefix_sums
   ```

2. **What Happens:**
   - **Automated Tests:**  
     The program first runs all the doctest unit tests. The test results are printed to the terminal.
   - **Interactive Mode:**  
     After the tests, you will be prompted to enter:
     - The number of elements for the array.
     - The array elements (each must be either +1 or -1).

   The program then displays whether the prefix sums are non-negative and/or non-positive.
---

## Summary

- **Compile:**  
  (
  ```bash
  g++ -std=c++11 prefix_sums.cpp -o prefix_sums
  ```

- **Run:**  
  ```bash
  ./prefix_sums
  ```

- **Test:**  
  The integrated doctest tests run automatically before the interactive prompt.

Enjoy using the Prefix Sums Checker!
