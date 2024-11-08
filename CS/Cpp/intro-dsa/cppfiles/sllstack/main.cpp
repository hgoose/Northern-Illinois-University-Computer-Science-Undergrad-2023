#include <iostream>

// Define a node structure for use in the mystack class
struct node {
    node* next = nullptr; // Pointer to the next node in the stack
    int value = 0; // The value stored in this node

    node() = default; // Default constructor
    node(node* next, int value) : next(next), value(value) {}; // Constructor initializing members
};

// Define a class to represent a stack using a linked list
class mystack {
    node* stack_top = nullptr; // Pointer to the top node of the stack
    size_t m_size = 0; // Current size of the stack

public:
    // Allow ostream to access private members of mystack for printing
    friend std::ostream& operator<<(std::ostream& os, const mystack& obj);

    // Copy constructor
    mystack(const mystack& x) {
        this->stack_top = nullptr; // Initialize stack_top to nullptr
        this->m_size = x.size(); // Copy size from x
        clear(); // Clear existing content
        clone(x); // Deep copy nodes from x
    }

    // Copy assignment operator
    mystack& operator=(const mystack& x) {
        if (this != &x) { // Check for self-assignment
            this->stack_top = nullptr; // Reset stack_top
            this->m_size = x.size(); // Copy size from x
            clear(); // Clear existing content
            clone(x); // Deep copy nodes from x
        }
        return *this; // Return a reference to the current object
    }

        // Return the current size of the stack
    size_t size() const {
        return this->m_size;
    }

    // Check if the stack is empty
    bool empty() const {
        return this->m_size == 0;
    }

    // Remove the top element from the stack
    void pop(){
        node* del = this->stack_top; // Temporary pointer to the top node
        this->stack_top = this->stack_top->next; // Move the top pointer to the next node
        delete del; // Deallocate the removed node
        (this->m_size)--; // Decrement the size of the stack
    }

    // Clear all elements from the stack
    void clear(){
        while (this->stack_top != nullptr) { // While there are nodes in the stack
            this->pop(); // Remove the top node
        }
    }

    // Access the value of the top element in the stack
    const int& top() const{
        return stack_top->value;
    }

    // Add a new element to the top of the stack
    void push(int value){
        node* new_node = new node(this->stack_top, value); // Create a new node with the given value
        this->stack_top = new_node; // Make the new node the top of the stack
        ++this->m_size; // Increment the size of the stack
    }
    // Clone the stack from another mystack object
    void clone(const mystack& obj) {
        if (obj.stack_top == nullptr) { // If the source stack is empty
            this->stack_top = nullptr; // Make the current stack empty
            return;
        }
        stack_top = new node(nullptr, obj.stack_top->value); // Copy the top node
        node* src = obj.stack_top->next; // Pointer to traverse the source stack
        node* dest = stack_top; // Pointer to build the current stack

        while(src != nullptr) { // While there are more nodes to copy
            dest->next = new node(nullptr, src->value); // Copy the node
            dest = dest->next; // Move to the next node
            src = src->next; // Move to the next source node
        }
        this->m_size = obj.m_size; // Copy the size
    }

    // Destructor to clean up the stack
    ~mystack() {
        this->clear(); // Clear the stack
    }
};

// Overload the << operator to print the stack
std::ostream& operator<<(std::ostream& os, const mystack& obj) {
    node* current = obj.stack_top; // Start from the top of the stack

    if (current == nullptr) { return os; }

    while (current != nullptr) { // Iterate through the stack
        os << current->value; // Print the current node's value
        if (current->next != nullptr) {
                os << ", "; // If this is not the last node, print a comma and a space
            }
            current = current->next; // Move to the next node
        }

    return os;
}

int main(int argc, char* argv[]) {

    return 0;

}
