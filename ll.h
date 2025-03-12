#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>

/**
 * A simple Node struct for a singly‐linked list.
 */
struct Node {
    int data;
    Node* next;

    // Constructor
    explicit Node(int dataVal);

    // Copy constructor (deep copy any subsequent nodes)
    Node(const Node &other);

    // Move constructor
    Node(Node&& other) noexcept;

    // Move assignment operator
    Node& operator=(Node&& other) noexcept;

    // Destructor (recursively deletes subsequent nodes)
    ~Node();
};

// ---- Linked‐List Function Declarations ----
Node* build_linked_list(const std::vector<int>& values);
void print_linked_list(const Node* head);
void delete_entire_linked_list(Node*& head);

int  get_linked_list_data_item_value(Node* root, int node_number);
void delete_list_element(Node*& head, int node_number);

#endif // LINKEDLIST_H
