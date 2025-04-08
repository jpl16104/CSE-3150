# Jean Code – Tokenizer Lab

## Overview

This lab implements a **Tokenizer** application in C++ that reads a text file, extracts words using regular expressions, and assigns each unique word a numeric token. The application supports quick lookups in both directions: from word to token and from token to word.

### Compile and run
```bash
g++ -std=c++11 -Wall -o tokenizer tokenizer.cpp
./tokenizer input.txt

```

## Application Architecture

### Components

- **Input Handling Layer:**
  - **Command-Line Interface:**  
    Parses command-line arguments to accept a text file as input.
  - **File I/O Module:**  
    Opens the file and reads its entire content into a string.

- **Tokenization Core:**
  - **Tokenizer Class:**  
    Encapsulates the tokenization logic.
    - **Regex Processing:**  
      Uses C++11’s `<regex>` library with the pattern `\\b\\w+\\b` to extract words.  
      Utilizes the Iterator Pattern via `std::sregex_iterator` for traversing matches.
    - **Data Structures:**
      - `std::unordered_map<std::string, int>`:  
        Provides fast word-to-token lookup.
      - `std::vector<std::string>`:  
        Stores words such that the token (an integer) directly corresponds to the index, enabling reverse lookup.
  - **Software Patterns Used:**
    - **Facade Pattern:**  
      The `Tokenizer` class offers a simplified interface to the file I/O, regex matching, and token mapping functionalities.
    - **Iterator Pattern:**  
      Employed by using `std::sregex_iterator` to iterate over regex matches.
    - **Separation of Concerns:**  
      Distinct handling of file reading, tokenization logic, and output operations.
    - **Encapsulation:**  
      Internal data structures (the map and vector) are hidden behind the public interface of the class.

- **Output Layer:**
  - **Console Output:**  
    Prints the complete mapping of tokens to words and supports lookup operations.

## User-Flow Diagram

```plaintext
   +--------------------------+
   |         Start            |
   +--------------------------+
              |
              v
   +--------------------------+
   | Launch Application       |
   | (Input file as argument) |
   +--------------------------+
              |
              v
   +--------------------------+
   | Parse Command-Line Args  |
   +--------------------------+
              |
              v
   +--------------------------+
   | Open and Read File       |
   +--------------------------+
              |
              v
   +--------------------------+
   | Extract Words using      |
   | Regex (Tokenizer Core)   |
   +--------------------------+
              |
              v
   +--------------------------+
   | Map Unique Words to      |
   | Numeric Tokens           |
   +--------------------------+
              |
              v
   +--------------------------+
   | Output/Lookup Operations |
   +--------------------------+
              |
              v
   +--------------------------+
   |          End             |
   +--------------------------+
