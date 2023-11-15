#include <iostream>

using std::cout;

class Node final {
public:
    /**
     * Ctor
     * @param val noe value
     */
    explicit Node(int val) {
        value = val;
        next = nullptr;
        prev = nullptr;
    }

    int value;

    Node *next;

    Node *prev;
};

class DoublyLinkedList final {
private:
    Node *head;

    Node *tail;

    int length;

public:
    /**
     * Ctor
     * @param value First node value
     */
    explicit DoublyLinkedList(int value) {
        Node *newNode = new Node(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    /**
     * Dtor
     */
    ~DoublyLinkedList() {
        Node *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        auto temp = head;
        if (temp == nullptr) {
            std::cout << "empty\n";
            return;
        }
        while (temp->next != nullptr) {
            std::cout << temp->value << " <-> ";
            temp = temp->next;
        }
        std::cout << temp->value << '\n';
    }

    Node *getHead() {
        return head;
    }

    Node *getTail() {
        return tail;
    }

    int getLength() const {
        return length;
    }

    void makeEmpty() {
        auto current = head;
        while (current) {
            auto nodeToDelete = current;
            current = current->next;
            delete nodeToDelete;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    void append(int value) {
        auto newNode = new Node(value);
        if (!length) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }

    void deleteLast() {
        if (!length) {
            return;
        }
        auto temp = tail;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        length--;
    }

    void prepend(int value) {
        auto newNode = new Node(value);
        if (!length) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    void deleteFirst() {
        if (!length) {
            return;
        }
        auto temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        length--;
    }

    Node *get(int index) {
        if (index < 0 || index >= length) {
            return nullptr;
        }
        auto temp = head;
        if (index < length / 2) {
            for (int i = 0; i < index; ++i) {
                temp = temp->next;
            }
        } else {
            temp = tail;
            for (int i = length - 1; i > index; --i) {
                temp = temp->prev;
            }
        }
        return temp;
    }

    bool set(int index, int value) {
        auto temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

    bool insert(int index, int value) {
        if (index < 0 || index > length) {
            return false;
        }
        if (!index) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }

        auto newNode = new Node(value);
        auto before = get(index - 1);
        auto after = before->next;
        newNode->prev = before;
        newNode->next = after;
        before->next = newNode;
        after->prev = newNode;
        length++;
        return true;
    }

    void deleteNode(int index) {
        if (!index) {
            deleteFirst();
            return;
        }
        if (index == length - 1) {
            deleteLast();
            return;
        }

        auto temp = get(index);
        if (!temp) {
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        length--;
    }

    void reverse() {
        if (length < 2) {
            return;
        }

        auto current = head;
        Node *temp = nullptr;

        for (int i = 0; i < length; ++i) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }

    void swapFirstLast() {
        if (length < 2) {
            return;
        }
        int temp = head->value;
        head->value = tail->value;
        tail->value = temp;
    }

    void swapPairs() {
        Node temp(0);
        temp.next = head;

        auto tempHead = &temp;
        while (head && head->next) {
            auto first = head;
            auto second = head->next;

            tempHead->next = second;
            first->next = second->next;
            second->next = first;

            second->prev = tempHead;
            first->prev = second;
             if(first->next) {
                first->next->prev = first;
             }

             head = first->next;
             tempHead = first;
        }
        head = temp.next;
        if(head) {
            head->prev = nullptr;
        }
    }

    bool isPalindrome() {
        if(!length || length == 1) {
            return true;
        }

        auto backwardNode = tail;
        auto forwardNode = head;

        while (backwardNode != forwardNode) {
            if(backwardNode->value != forwardNode->value) {
                return false;
            }
            backwardNode = backwardNode->prev;
            forwardNode = forwardNode->next;
        }
        return true;
    }
};

int main() {
    return 0;
}
