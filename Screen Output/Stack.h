/*
    Stack.h
    Unit 4: Screen Output - Stack data structure for undo functionality
    Name: Aarush Muralinathan
*/

#ifndef STACK_H
#define STACK_H
#include "../Song.h"

class Stack {
private:
    struct StackNode {
        Song data;
        StackNode* next;
        StackNode(Song s) : data(s), next(nullptr) {}
    };
    StackNode* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack() { clear(); }
    
    void push(Song item) {
        StackNode* newNode = new StackNode(item);
        newNode->next = topNode;
        topNode = newNode;
    }
    
    Song pop() {
        if (isEmpty()) return Song();
        StackNode* temp = topNode;
        Song poppedItem = temp->data;
        topNode = topNode->next;
        delete temp;
        return poppedItem;
    }
    
    bool isEmpty() const { return topNode == nullptr; }
    
    void clear() {
        while (!isEmpty()) { pop(); }
    }
};
#endif