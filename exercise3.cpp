#include <iostream>
using namespace std;

struct IntNode {
    int value; 
    IntNode* next;
    IntNode(int value): next(nullptr) {
        this->value = value;
    }
};

struct IntList {
    private:
        IntNode* head;
    public:
        // Default constructor
        IntList(): head(nullptr) {}
        
        // Delete all nodes when deconstructing
        ~IntList() {
            IntNode* cur_node = head;
            while (cur_node->next != nullptr) {
                IntNode* to_delete = cur_node;
                cur_node = cur_node->next;
                delete to_delete;
                to_delete = NULL;
            }
            delete cur_node;
            cur_node = NULL;
        }

        // Create first node function
        IntNode* createFirst(int num) {
            IntNode* first_node = new IntNode(num); // instantiates a new node called first_node
            this->head = first_node; // first_node becomes the head of its IntList
            return first_node;
        }
        
        // Insert node after any other node
        IntNode* insertAfter(int num, IntNode* adj) {
            if (adj == nullptr || adj == NULL ) return NULL; // safety check if the passed argument not NULL
            IntNode* new_node = new IntNode(num); // instantiates a new node named new_node that holds the int number in the paramet
            new_node->next = adj->next; // the next node of new_node points to the next node of adj, essentially making new_node go after adj
            adj->next = new_node;
            return new_node;
        }

        // Insert node before any other node
        IntNode* insertBefore(int num, IntNode* adj) {
            if (adj == nullptr || adj == NULL ) return NULL; // safety check if the passed argument not NULL
            IntNode* new_node = new IntNode(num); // instantiates a new node named new_node that holds the int number in the paramet
            new_node->next = adj; // the next node of new_node points to adj, essentially making new_node go before adj
            if (head == adj) head = new_node; // the new_node becomes the new head if adj is the head
            return new_node;
        }

        // get first node
        IntNode* getFirst() {
            if (head == nullptr) return NULL; // if the first node is nullptr, then return NULL
            return head;
        }

        // get next node
        IntNode* getNext(IntNode* node) {
            if (node == nullptr || node->next == nullptr) return NULL; // if the node or its next iteration is a nullptr, then return NULL
            else {
                IntNode* nextNode = node->next; // otherwise, the function takes in the next node and returns it
                return nextNode;
            }
        }

        // delete a node
        void deleteNode(IntNode* node) {
            // if head or node is nullptr
            if (head == nullptr || node == nullptr) return;
            
            // if node is head
            if (node == head) {
                head = head->next; // the node that comes after the head becomes the new head
                delete node; // deletes the former head node
                return;
            }
            
            // traverse the nodes until the node to be deleted to account for pointer
            IntNode* current = head;
            while (current->next && current->next != node) current = current->next; 
            
            // delete node
            if (current->next == node){
                current->next = node->next;
                delete node;
            }
        }
    
};

struct IntStack {
    private:
        int size;
        IntList* list;
    public:
        IntStack(): size(0) {
            list = new IntList();
        }
        ~IntStack() {
            delete list;
            list = NULL;
        }
        void push(int num) {
            IntNode* head = list->getFirst(); // instantiate a new node containing the head
            list->insertBefore(num, head); // adds in the node on top of stack
            if (size == 0) list->createFirst(num);
            size++; // increments size of the stack
        }
        int pop() {
            if (size == 0) return 0;
            IntNode* head = list->getFirst(); // instantiate the top node of the stack
            int popped = head->value; // get the int value of the head and store it to popped
            list->deleteNode(head); // remove the top node of the stack in intlist
            if(size >= 1) size--; // size decrements unless it is less than 1 (which practically means if its 0)
            return popped;
        }
        int getSize() { return size; } // returns the size of the stack
};

int main() {
    cout << "Structs Group Exercise Demo\nEsteban, Funelas, Verial | CSCI 51.02-B" << endl;
    // IntStack* new_stack = new IntStack();
    // new_stack->push(1);
    // new_stack->push(2);
    // new_stack->push(3);
    // new_stack->push(4);
    // new_stack->push(5);
    // new_stack->push(6);
    // new_stack->push(7);
    // for (int i=0; i<10; i++) {
    //     cout << new_stack->pop() << endl;
    // }
    // new_stack->push(6);
    // new_stack->push(7);
    // new_stack->push(6);
    // new_stack->push(7);
    // new_stack->push(9);
    // new_stack->push(4);
    // for (int i=0; i<2; i++) {
    //     cout << new_stack->pop() << endl;
    // }
    // delete new_stack;
    // new_stack = NULL;
    return 0;
}
