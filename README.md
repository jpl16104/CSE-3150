#Cosine Distance Calculator Jean Lara
## Overview
This C++ program reads vectors of doubles from an input file and calculates all pairwise cosine distances (angles) between these vectors. The results are sorted so that the closest vectors (i.e., the smallest cosine angles) are displayed first.

## Features
- **Input Parsing:** Reads vectors from a file (one vector per line, with space-separated doubles).
- **Validation:** Ensures all vectors are of the same dimension.
- **Cosine Angle Calculation:** Computes the cosine angle between each pair of vectors using the dot product and Euclidean norms.
- **Sorting:** Orders the vector pairs by ascending cosine angle.
- **Output:** Displays the sorted pairs along with the computed angles (in radians).

## Requirements
- A C++ compiler supporting C++11 (e.g., `g++`).
- A text file containing vectors, where each vector is on a new line.

## Usage

### 1. Compile the Program
```bash
g++ -std=c++11 -o cosine_pairs cosine_pairs.cpp
```
### 2. Create an Input File

Create a file (e.g., `test_vectors.txt`) with each line representing a vector. For example: 
```
1 0
0 1
1 1
1 2
```
### 3. Run the Program
./cosine_pairs test_vectors.txt

## User-Flow Diagram

Below is a simple user-flow diagram illustrating the steps from input to output:
```
flowchart TD
    A[Start]
    B[Read Vectors from Input File]
    C[Validate Vector Dimensions]
    D[Compute Pairwise Cosine Angles]
    E[Sort Pairs by Ascending Angle]
    F[Display Sorted Results]
    G[End]

    A --> B
    B --> C
    C --> D
    D --> E
    E --> F
    F --> G
```
