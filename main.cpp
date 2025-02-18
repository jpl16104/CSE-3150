#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "ll.h"
#include <iostream>
#include <vector>
#include <stdexcept>

// ---------------- DOCTEST TESTS ----------------

// Build list tests
TEST_CASE("build_linked_list") {
    SUBCASE("Empty vector returns nullptr") {
        Node* head = build_linked_list({});
        CHECK(head == nullptr);
        delete_entire_linked_list(head);
    }
    SUBCASE("Non-empty vector produces correct list") {
        Node* head = build_linked_list({1, 2, 3});
        REQUIRE(head != nullptr);

        CHECK_EQ(head->data, 1);
        CHECK_NE(head->next, nullptr);
        CHECK_EQ(head->next->data, 2);
        CHECK_NE(head->next->next, nullptr);
        CHECK_EQ(head->next->next->data, 3);
        CHECK_EQ(head->next->next->next, nullptr);

        delete_entire_linked_list(head);
        CHECK_EQ(head, nullptr);
    }
}

TEST_CASE("delete_entire_linked_list") {
    Node* head = build_linked_list({10, 20, 30});
    delete_entire_linked_list(head);
    CHECK_EQ(head, nullptr);
}

// etc... add more tests as needed
// ...

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
