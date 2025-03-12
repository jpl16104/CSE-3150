# Jean Code Lab Week 4: Linked List with Move Semantics

This lab exercise extends a basic singly linked list implementation by adding move semantics to the `Node` struct. The new features include:
- **Move Constructor:** Transfers ownership of the node’s data and its subsequent chain from one node to another.
- **Move Assignment Operator:** Frees the existing chain and then transfers ownership from another node, ensuring proper resource management.

The program includes automated tests using the [doctest](https://github.com/onqtam/doctest) framework. After the tests pass, the program enters an interactive mode where you can create, display, and modify a linked list.

---

## Requirements

- A C++ compiler (e.g., g++)
- The header-only [doctest](https://github.com/onqtam/doctest) library  
  (Ensure that `doctest.h` is in the same directory as your source code or in your include path.)

---

## Files

- **ll.h:** Contains the declarations for the `Node` struct (including the move constructor and move assignment operator) and linked list functions.
- **ll.cpp:** Implements the `Node` functionalities and linked list functions.
- **main.cpp:** Contains the `main()` function, which runs doctest unit tests and provides an interactive mode for linked list operations.

---

## How to Compile

1. Open a terminal in the directory containing `main.cpp`, `ll.cpp`, and `ll.h`.
2. Compile the program using:
   ```bash
   g++ -std=c++17 main.cpp ll.cpp -o linked_list_lab
   ```
## How to Run and Test

1. Run the compiled program by executing:
```bash
./ll
```
2. What Happens:

- Automated Tests:
  The program first runs all the doctest unit tests and prints the results to the terminal.
- Interactive Mode:
    After the tests, you will be prompted to:
      - Specify the number of elements for the linked list.
      - Enter the integer elements to create the list.
      - Optionally, choose a position to delete a node.
    - The program then prints the linked list before and after deletion operations.
