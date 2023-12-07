#include <iostream>
#include <vector>

class Node {
public:
    std::string key;
    int value;
    Node *next;

    Node(std::string key, int value) {
        this->key = key;
        this->value = value;
        next = nullptr;
    }
};

class HashTable {
private:
    static const int SIZE = 7;
    Node *dataMap[SIZE];

    int hash(std::string key) {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            int asciiValue = int(key[i]);
            hash = (hash + asciiValue * 23) % SIZE;
        }
        return hash;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            dataMap[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            auto head = dataMap[i];
            auto temp = head;
            while (head) {
                head = head->next;
                delete temp;
                temp = head;
            }
        }
    }

    void printTable() {
        for (int i = 0; i < SIZE; i++) {
            std::cout << "Index " << i << ": ";
            if (dataMap[i]) {
                std::cout << "Contains => ";
                auto temp = dataMap[i];
                while (temp) {
                    std::cout << "{" << temp->key << ", " << temp->value << "}";
                    temp = temp->next;
                    if (temp) {
                        std::cout << ", ";
                    }
                }
                std::cout << '\n';
            } else {
                std::cout << "Empty" << std::endl;
            }
        }
    }

    void set(std::string key, int value) {
        int index = hash(key);
        auto newNode = new Node(key, value);
        if (dataMap[index] == nullptr) {
            dataMap[index] = newNode;
        } else {
            Node *temp = dataMap[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int get(std::string key) {
        int index = hash(key);
        auto temp = dataMap[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return 0;
    }

    std::vector<std::string> keys() {
        std::vector<std::string> keys;

        for (int i = 0; i < SIZE; ++i) {
            auto temp = dataMap[i];
            while (temp) {
                keys.emplace_back(temp->key);
                temp = temp->next;
            }
        }

        return keys;
    }
};
