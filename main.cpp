#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "ll.h"
#include <iostream>
#include <vector>
#include <stdexcept>

// ---------------- DOCTEST TESTS ----------------

TEST_CASE("Node move constructor - single node") {
    // Create a single-node list
    Node original(10);

    // Move-construct a new Node from 'original'
    Node moved(std::move(original));

    // Check that 'moved' took the data
    CHECK_EQ(moved.data, 10);
    CHECK(moved.next == nullptr);

    // 'original' is now in a moved-from state
    CHECK(original.next == nullptr);
}

TEST_CASE("Node move constructor - chain of nodes") {
    // Create a chain of nodes
    Node original(1);
    original.next = new Node(2);
    original.next->next = new Node(3);

    // Move-construct 'moved' from 'original'
    Node moved(std::move(original));

    // Verify 'moved' contains the entire chain
    CHECK_EQ(moved.data, 1);
    REQUIRE(moved.next != nullptr);
    CHECK_EQ(moved.next->data, 2);
    REQUIRE(moved.next->next != nullptr);
    CHECK_EQ(moved.next->next->data, 3);
    CHECK(moved.next->next->next == nullptr);

    // The old list should be "moved from"
    CHECK(original.next == nullptr);
}

TEST_CASE("Node move assignment operator") {
    // Create two separate chains
    Node listA(10);
    listA.next = new Node(20);

    Node listB(100);
    listB.next = new Node(200);

    // Move-assign listB = std::move(listA)
    listB = std::move(listA);

    // Check that listB took over listA's chain
    CHECK_EQ(listB.data, 10);
    REQUIRE(listB.next != nullptr);
    CHECK_EQ(listB.next->data, 20);
    CHECK(listB.next->next == nullptr);

    // listA should now be "moved from"
    CHECK(listA.next == nullptr);
}

// ------------- OUR CUSTOM MAIN -------------
int main(int argc, char** argv)
{
    // 1) Create a doctest context
    doctest::Context context;
    // 2) Apply command-line args to configure test run
    context.applyCommandLine(argc, argv);

    // 3) Run the tests
    int testResult = context.run();

    // If the user only wants tests (e.g. `./program --success`),
    // stop here if needed:
    if (context.shouldExit()) {
        return testResult; // propagate test result
    }

    // 4) Proceed with user interaction after tests:

    // Ask how many elements the user wants in the list
    std::cout << "How many elements do you want to create? ";
    int n;
    std::cin >> n;

    // Collect user input into a vector
    std::vector<int> values;
    values.reserve(n);

    std::cout << "Please enter " << n << " integer(s):\n";
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        values.push_back(val);
    }

    // Build the linked list
    Node* head = build_linked_list(values);

    // Print the linked list
    std::cout << "Here is the linked list you created:\n";
    print_linked_list(head);

    // Example: ask user for a position to delete
    std::cout << "Enter a position to delete (1-based), or 0 to skip: ";
    int pos;
    std::cin >> pos;
    if (pos > 0) {
        delete_list_element(head, pos);
        std::cout << "After deletion:\n";
        print_linked_list(head);
    }

    // Clean up
    delete_entire_linked_list(head);

    return testResult; 
}
