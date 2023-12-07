class Node {
public:
    int value;
    Node *left;
    Node *right;

    Node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};


class BinarySearchTree {
private:
    Node *root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void destroy(Node *currentNode) {
        if (!currentNode) {
            return;
        }
        if (currentNode->left) {
            destroy(currentNode->left);
        }
        if (currentNode->right) {
            destroy(currentNode->right);
        }
        delete currentNode;
    }

    ~BinarySearchTree() {
        destroy(root);
    }

    Node *getRoot() {
        return root;
    }

    bool insert(int value) {
        auto newNode = new Node(value);
        if (!root) {
            root = newNode;
            return true;
        }
        auto temp = root;
        while (true) {
            if (newNode->value == temp->value) {
                return false;
            }
            if (newNode->value < temp->value) {
                if (!temp->left) {
                    temp->left = newNode;
                    return true;
                }
                temp = temp->left;
            } else {
                if (!temp->right) {
                    temp->right = newNode;
                    return true;
                }
                temp = temp->right;
            }
        }
    }

    bool contains(int value) {
        if (!root) {
            return false;
        }

        auto temp = root;
        while (temp) {
            if (value == temp->value) {
                return true;
            }
            if (value > temp->value) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return false;
    }

};
