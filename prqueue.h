/// @file prqueue.h
/// @author Shaan Kohli
/// @date October 30, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child
    };
    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)
    
public:

    // default constructor:
    // Creates an empty priority queue.
    // O(1)    
    prqueue() {
        root = nullptr;
        sz = 0;
        curr = nullptr;
    }

    // operator=
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    prqueue& operator=(const prqueue& other) {

        // checks that you do not assign the tree to itself
        if (this == &other) {
            return *this;
        }

        clear();

        // copies the root node of other prqueue
        // and assigns it to root of this prqueue
        root = copy(other.root);

        // makes other prqueue and this prqueue have same size
        sz = other.sz;

        return *this;
    }

    // helper function for operator=
    // creates a copy of a NODE and its children
    // returns the copy node
    NODE* copy(NODE* node) {
        // handles base case
        if (node == nullptr) {
            return nullptr;
        }

        // creates a new node and copies the values from input node
        NODE *newNode = new NODE;
        newNode->priority = node->priority;
        newNode->value = node->value;
        newNode->dup = node->dup;
        newNode->parent = nullptr;

        // recursively copies the left and right children of the node
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);

        // handles duplicates with the same priority
        if (node->link != nullptr) {
            newNode->link = new NODE;
            NODE *newLink = newNode->link;
            NODE *oldLink = node->link;

            // goes through linked nodes and copies the values
            while (oldLink != nullptr) {
                newLink->priority = oldLink->priority;
                newLink->value = oldLink->value;
                newLink->dup = oldLink->dup;
                newLink->parent = nullptr;
                newLink->left = nullptr;
                newLink->right = nullptr;

                // checks if there is another node to link, allocates a new node if that is true
                newLink->link = (oldLink->link != nullptr) ? new NODE : nullptr;

                // moves to the next linked node
                oldLink = oldLink->link;
                newLink = newLink->link;
            }
        }
        // sets link to nullptr if there is not a linked node
        else {
            newNode->link = nullptr;
        }

        // returns copied node
        return newNode;
    }

    // helper function for the clear function
    void clearHelper(NODE* node) {

        // handles base case
        if (node == nullptr) {
            return;
        }

        // clears the left and right subtree of the BST
        clearHelper(node->left);
        clearHelper(node->right);

        NODE *temp = node->link;
        while (temp != nullptr) {
            NODE *toDelete = temp;
            temp = temp->link;
            delete toDelete;
        }

        // frees the memory from the node
        delete node;
    }

    // clear:
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    void clear() {
        
        // clears the BST, sets the root to a nullptr, and updates the size
        clearHelper(root);
        root = nullptr;
        sz = 0;
    }

    // destructor:
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    ~prqueue() {
        clear();
    }
    
    // enqueue:
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    void enqueue(T value, int priority) {
        
        // creates new node and sets initial values for it
        NODE *newNode = new NODE;
        newNode->value = value;
        newNode->priority = priority;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->link = nullptr;
        newNode->dup = false;

        // if tree is empty, the new node is the root
        if (root == nullptr) {
            root = newNode;
            newNode->parent = nullptr;
        }
        else {
            NODE *temp = root;

            // loops to find proper spot for node
            while (true) {

                // checks if new node's priority is less
                if (priority < temp->priority) {

                    // if there is no left child, the new node becomes the left child 
                    if (temp->left == nullptr) {
                        temp->left = newNode;
                        newNode->parent = temp;
                        break;
                    }

                    // moves to left child
                    temp = temp->left;
                }

                // checks if new node's priority is more
                else if (priority > temp->priority) {

                    // if there is no right child, the new node becomes the right child
                    if (temp->right == nullptr) {
                        temp->right = newNode;
                        newNode->parent = temp;
                        break;
                    }

                    // moves to right child
                    temp = temp->right;
                }

                // if priorities are equal
                else {

                    // if there is no linked node, it links the new node and 
                    // sets parent of node and marks node as a duplicate
                    if (temp->link == nullptr) {
                        temp->link = newNode;
                        newNode->parent = temp;
                        temp->dup = true;
                        break;
                    }

                    // creates temporary node and traverses through linked list to find last node
                    NODE *tempLink = temp->link;
                    while (tempLink->link != nullptr) {
                        tempLink = tempLink->link;
                    }

                    // links new node at the end of the list and sets the parent of the node
                    tempLink->link = newNode;
                    newNode->parent = tempLink;
                    newNode->dup = true;
                    break;
                }
            }
        }

        // increments the size of the priority queue
        sz++;
    }

    // dequeue:
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    T dequeue() {

        // handles case where queue is empty
        if (root == nullptr) {
            // returns default constructor of T
            return T();
        }

        // finds the node with the highest priority(smallest number)
        NODE *toDelete = root;
        while (toDelete->left != nullptr) {
            toDelete = toDelete->left;
        }

        // saves value to be dequeued and returned
        T valueOut = toDelete->value;

        // checks if node has linked node with same priority
        if (toDelete->link != nullptr) {
            NODE *temp = toDelete->link;
            toDelete->value = temp->value;
            toDelete->priority = temp->priority;
            toDelete->link = temp->link;
            delete temp;
        }
        else {
            // if node to delete has right child, find the successor
            if (toDelete->right != nullptr) {
                NODE *suc = toDelete->right;
                while (suc->left != nullptr) {
                    suc = suc->left;
                }

                toDelete->value = suc->value;
                toDelete->priority = suc->priority;
                toDelete->link = suc->link;

                // adjusts the pointers to remove the successor from the tree
                if (suc->parent->left == suc) {
                    suc->parent->left = suc->right;
                }
                else {
                    suc->parent->right = suc->right;
                }
                if (suc->right != nullptr) {
                    suc->right->parent = suc->parent;
                }

                delete suc;

                
            }
        
            else {
                // if node to delete does not have right child, remove it
                if (toDelete->parent != nullptr) {
                    if (toDelete->parent->left == toDelete) {
                        toDelete->parent->left = nullptr;
                    }
                    else {
                        toDelete->parent->right = nullptr;
                    }
                }
                else {
                    // if node to delete is the root, update root pointer
                    root = nullptr;
                }
                delete toDelete;
            }
        }

        // decreases size of priority queue and return dequeued node
        sz--;
        return valueOut; 
    }
    
    // Size:
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)    
    int size() {
        return sz; 
    }
    
    // begin
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    // O(logn), where n is number of unique nodes in tree
    void begin() {
        
        // starts from root of BST and checks if root is nullptr
        curr = root;
        if (curr == nullptr) {
            return;
        }

        // traverses to the leftmost node (smallest priority)
        while (curr->left != nullptr) {
            curr = curr->left;
        }
    }
    
    // next
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    // O(logn), where n is the number of unique nodes in tree
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    bool next(T& value, int &priority) {
        
        // handles base case
        if (curr == nullptr) {
            return false;
        }

        // handles duplicate priorities
        if (curr->link != nullptr) {
            value = curr->value;
            priority = curr->priority;
            curr = curr->link;
            return true;
        }

        // stores current value and priority
        value = curr->value;
        priority = curr->priority;

        while (curr->parent != nullptr 
            && curr->parent->priority == curr->priority) 
        {
            curr = curr->parent;    
        }

        // if there is a right child, this goes to right child then goes all the way left
        if (curr->right != nullptr) {
            // cout << "Moving Right: " << endl;
            curr = curr->right;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
        }
        // if there is no right child, this goes back to find the next node
        else {
            
            NODE *parent = curr->parent;
            while (parent != nullptr && curr == parent->right) {
                curr = parent;
                parent = curr->parent;
            }
            curr = parent;

        }

        // check if no next element was found
        if (curr == nullptr) {
            return false;
        }

        // next element was found and properly stored
        return true;
    }

    // helper function for the toString Function
    // no return
    void toStringHelper(NODE* node, stringstream& ss) {
        // handles base case
        if (node == nullptr) {
            return;
        }

        // recursive call to the left subtree
        toStringHelper(node->left, ss);

        // writes current node's priority and value to the stringstream
        ss << node->priority << " value: " << node->value << endl;

        // handles nodes with duplicate priorities
        NODE *tempLink = node->link;
        while (tempLink != NULL) {
            ss << tempLink->priority << " value: " << tempLink->value << endl;
            tempLink = tempLink->link;
        }

        // recrusive call to the right subtree
        toStringHelper(node->right, ss);
    }

    // toString:    
    // Returns a string of the entire priority queue, in order
    string toString() {
        stringstream ss;

        // calls helper function to perform recursion
        toStringHelper(root, ss);

        // converts the stringstream into a string and returns it
        return ss.str(); 
    }
    
    // peek:
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    T peek() {

        // handles case where queue is empty and returns default constructor
        if (root == nullptr) {
            return T();
        }

        // finds node with highest priority (smallest number)
        NODE *highestPriority = root;
        while (highestPriority->left != nullptr) {
            highestPriority = highestPriority->left;
        }

        // returns value of highest priority but does not remove it
        return highestPriority->value; 
        
    }
    

    // helper function for operator==
    // compares the nodes from this priority queue and the other priority queue
    // returns a recursive call to both the left and right children of this and other nodes
    bool compareNodes(NODE* a, NODE* b) const{

        // handles base cases
        if (a == nullptr && b == nullptr) {
            return true;
        }
        if (a == nullptr || b == nullptr) {
            return false;
        }

        // checks if node value or priority are different and returns false if they are
        if (a->value != b->value || a->priority != b->priority) {
            return false;
        }

        // recursively compares linked nodes
        if (!compareNodes(a->link, b->link)) {
            return false;
        }

        // recursively compares left and right children of nodes
        return compareNodes(a->left, b->left) && compareNodes(a->right, b->right);
    }

    // ==operator
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    bool operator==(const prqueue& other) const {
        return compareNodes(this->root, other.root);
    }
    
    // getRoot - Do not edit/change!
    // Used for testing the BST.
    // return the root node for testing.
    void* getRoot() {
        return root;
    }
};
