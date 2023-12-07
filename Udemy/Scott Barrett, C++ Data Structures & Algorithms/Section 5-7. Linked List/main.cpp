#include <iostream>
#include <unordered_set>

using std::cout;

class Node final {
public:
    Node(int val) noexcept : value(val), next(nullptr) {}

    Node *next;

    int value;
};

class LinkedList final {
public:
    LinkedList(int value) {
        head = new Node(value);
        tail = head;
        length = 1;
    }

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    ~LinkedList() {
        auto temp = head;
        while (temp) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void append(int value) {
        auto newNode = new Node(value);
        if (!length) {
            head = newNode;
            tail = head;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void print() {
        auto temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << '\n';
    }

    void prepend(int value) {
        auto newNode = new Node(value);
        if (!length) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    void deleteFirst() {
        std::cout << "Deleting the first node\n";
        switch (length) {
            case 0:
                return;
            case 1:
                delete head;
                head = nullptr;
                tail = nullptr;
                break;
            default:
                auto temp = head;
                head = head->next;
                delete temp;
                break;
        }
        length--;
    }

    Node *get(int index) {
        if (index >= length || index < 0) {
            return nullptr;
        }
        auto temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, int value) {
        auto temp = get(index);
        if (!temp) {
            return false;
        }
        temp->value = value;
        return true;
    }

    bool insert(int index, int value) {
        if (index > length || index < 0) {
            return false;
        }
        if (index == 0) {
            prepend(value);
        } else if (index == length) {
            append(value);
        } else {
            auto newNode = new Node(value);
            auto temp = get(index - 1);
            newNode->next = temp->next;
            temp->next = newNode;
            length++;
        }
        return true;
    }

    void deleteLast() {
        std::cout << "Deleting the last node\n";
        auto temp = head;
        auto pre = head;

        switch (length) {
            case 0:
                return;
            case 1:
                head = nullptr;
                tail = nullptr;
                break;
            default:
                while (temp->next) {
                    pre = temp;
                    temp = temp->next;
                }
                tail = pre;
                tail->next = nullptr;
                break;
        }
        delete temp;
        length--;
    }

    void deleteNode(int index) {
        if (index < 0 || index >= length) {
            return;
        }
        if (index == length - 1) {
            deleteLast();
            return;
        }
        if (index == 0) {
            deleteFirst();
            return;
        }
        auto prev = get(index - 1);
        auto temp = prev->next;
        prev->next = temp->next;
        delete temp;
        length--;
    }

    void reverse() {
        auto temp = head;
        head = tail;
        tail = temp;
        Node *after = nullptr;
        Node *before = nullptr;
        for (int i = 0; i < length; i++) {
            after = temp->next;
            temp->next = before;
            before = temp;
            temp = after;
        }
    }

    bool hasLoop() {
        Node *slow = head;
        Node *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

    Node *findMiddleNode() {
        if (head == tail) {
            return head;
        }
        auto slow = head;
        auto fast = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next->next;
            if (!fast) {
                break;
            }
        }
        return slow;
    }

    Node *findKthFromEnd(int k) {
        Node *slow = head;
        Node *fast = head;
        for (int i = 0; i < k; ++i) {
            if (!fast) {
                return nullptr;
            }
            fast = fast->next;
        }
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    void partitionList(int x) {
        if (head == nullptr) return;

        Node less(0);
        Node greater(0);
        Node *lessPtr = &less;
        Node *greaterPtr = &greater;
        Node *current = head;

        while (current) {
            if (current->value < x) {
                lessPtr->next = current;
                lessPtr = current;
            } else {
                greaterPtr->next = current;
                greaterPtr = current;
            }
            current = current->next;
        }

        greaterPtr->next = nullptr;
        lessPtr->next = greater.next;
        head = less.next;
    }

    void removeDuplicates() {
        Node *current = head;
        while (current) {
            Node *runner = current;
            while (runner->next) {
                if (runner->next->value == current->value) {
                    Node *temp = runner->next;
                    runner->next = runner->next->next;
                    delete temp;
                    length--;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }
    int binaryToDecimal() {
        int num = 0;
        Node *current = head;
        while (current) {
            num = num * 2 + current->value;
            current = current->next;
        }
        return num;
    }
    void reverseBetween(int m, int n) {
        if (head == nullptr) return;

        Node *dummy = new Node(0);
        dummy->next = head;
        Node *prev = dummy;

        for (int i = 0; i < m; i++) {
            prev = prev->next;
        }

        Node *current = prev->next;
        for (int i = 0; i < n - m; i++) {
            Node *temp = current->next;
            current->next = temp->next;
            temp->next = prev->next;
            prev->next = temp;
        }

        head = dummy->next;
        delete dummy;
    }

private:
    Node *head;

    Node *tail;

    int length;
};
