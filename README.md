# Lab Week 2: Balanced Lists

### **Name:** Jean Lara
### **Lab Name:** Lab Week 2: Balanced Lists

---

## Description

In this lab, we implement an algorithm that generates random sequences of +1 and -1, simulating the balancing of parentheses. The goal is to determine the proportion of "well-balanced" sequences, where the prefix sums of the sequence are non-negative and non-positive. This is done by generating random sequences of `2n` elements, where the first `n` elements are `1` and the last `n` elements are `-1`. The Fisher-Yates algorithm is used to shuffle the sequences randomly, and only the sequences that remain well-balanced are considered valid.

---

## Requirements

- **C++11** or higher.
- **Doctest** unit testing framework for running tests.
- **g++** or any C++11 compatible compiler.

---

## How to Compile

To compile the program, use the following command:

```bash
g++ -std=c++11 -o lab2 lab2.cpp
```

This will create an executable named `lab2` that you can run.

---

## Running the Program

Once compiled, run the program with:

```bash
./lab2
```

The program will:
1. Run all unit tests using Doctest.
2. Prompt the user for the number of matching symbol pairs (`n`).
3. Compute the proportion of well-balanced lists out of the total number of runs and display the result.

---

## Unit Tests

The program includes unit tests to ensure its correctness:

1. **Test for Well-Balanced List Validation**: Verifies that `isWellBalanced()` correctly identifies well-balanced sequences of +1 and -1.
2. **Test for Fisher-Yates Shuffle**: Ensures that the Fisher-Yates shuffle produces different orders of the list.
3. **Test for Proportion Calculation**: Tests that the proportion of well-balanced lists is between 0 and 1, inclusive.

These tests will run automatically when you execute the program.

---

## Project Files

This repository contains the following files:

- **lab2.cpp**: The main C++ file implementing the Fisher-Yates shuffle, list validation, and proportion calculation.
- **doctest.h**: The header-only unit testing library for Doctest.
- **README.md**: This file.

---

## Proportion of Well-Balanced Lists

The proportion of well-balanced lists is calculated by running a number of random permutations of the +1 and -1 sequences and determining how many of them are well-balanced. This proportion tends to converge after running the algorithm multiple times.

For example, after running the algorithm 10,000 times with `n = 5`, the program will output the following:
Total runs: 10000 Proportion of well-balanced lists: 0.3723

This shows that approximately 37% of the generated lists were well-balanced out of 10,000 runs.

---

## Files Included

- **lab2.cpp**: The main implementation file.
- **doctest.h**: The unit testing framework.
- **README.md**: Instructions and details about the project.

---

## Conclusion

This lab demonstrates the use of random number generation and the Fisher-Yates shuffle to simulate and validate well-balanced sequences. The results of the experiment can be analyzed by examining the proportion of well-balanced lists, and the unit tests ensure the correctness of the implementation.
