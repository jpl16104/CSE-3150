#include "ll.h"
#include <iostream>
#include <stdexcept>

// -------------- Node Implementations --------------

Node::Node(int dataVal)
    : data(dataVal), next(nullptr)
{}

Node::Node(const Node &other)
    : data(other.data), next(nullptr)
{
    // Deep copy of any subsequent nodes:
    if (other.next) {
        next = new Node(*other.next);
    }
}

Node::~Node()
{
    // Recursively delete the chain
    delete next;
}

// -------------- Linked‐List Function Implementations --------------

Node* build_linked_list(const std::vector<int>& values) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int val : values) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void print_linked_list(const Node* head) {
    const Node* current = head;
    while (current) {
        std::cout << current->data;
        if (current->next) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << '\n';
}

void delete_entire_linked_list(Node*& head) {
    delete head;  // triggers recursive destructor
    head = nullptr;
}

int get_linked_list_data_item_value(Node* root, int node_number) {
    if (!root || node_number < 1) {
        throw std::out_of_range("Invalid node number.");
    }
    Node* current = root;
    int count = 1;
    while (current && count < node_number) {
        current = current->next;
        ++count;
    }
    if (!current) {
        throw std::out_of_range("Node number exceeds list length.");
    }
    return current->data;
}

void delete_list_element(Node*& head, int node_number) {
    if (!head || node_number < 1) {
        return; // no-op
    }

    // If deleting the first element:
    if (node_number == 1) {
        Node* temp = head;
        head = head->next;
        temp->next = nullptr;  // detach so we don't delete the rest
        delete temp;
        return;
    }

    // Otherwise, find the node before the one to delete
    Node* current = head;
    int count = 1;
    while (current->next && count < (node_number - 1)) {
        current = current->next;
        ++count;
    }
    // If out of range, do nothing
    if (!current->next) {
        return;
    }

    Node* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    nodeToDelete->next = nullptr;  // detach
    delete nodeToDelete;
}
