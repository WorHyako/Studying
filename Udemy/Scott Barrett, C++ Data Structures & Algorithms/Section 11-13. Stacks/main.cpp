#include <iostream>
#include <climits>

class Node {
public:
    int value;
    Node *next;

    Node(int value) {
        this->value = value;
        next = nullptr;
    }
};

class Stack {
private:
    Node *top;
    int height;

public:
    Stack(int value) {
        Node *newNode = new Node(value);
        top = newNode;
        height = 1;
    }

    ~Stack() {
        Node *temp = top;
        while (top) {
            top = top->next;
            delete temp;
            temp = top;
        }
    }

    void printStack() {
        Node *temp = top;
        while (temp) {
            std::cout << temp->value << '\n';
            temp = temp->next;
        }
    }

    Node *getTop() {
        return top;
    }

    int topValue() {
        return top
               ? top->value
               : INT_MIN;
    }

    int getHeight() {
        return height;
    }

    void makeEmpty() {
        Node *temp;
        while (top) {
            temp = top;
            top = top->next;
            delete temp;
        }
        height = 0;
    }

    void push(int value) {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        height++;
    }

    int pop() {
        if (height == 0) {
            return INT_MIN;
        }

        Node* temp = top;
        int poppedValue = top->value;
        top = top->next;
        delete temp;
        height--;

        return poppedValue;
    }
};
