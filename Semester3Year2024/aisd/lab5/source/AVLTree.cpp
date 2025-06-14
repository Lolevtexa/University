#include "AVLTree.h"
#include <algorithm>
#include <iostream>

Node::Node(const Student& student) : data(student), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear(root);
}

int AVLTree::getHeight(Node* node) {
    if (!node) return 0;
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* AVLTree::insert(Node* node, const Student& student) {
    if (!node) {
        return new Node(student);
    }
    if (strcmp(student.student_id, node->data.student_id) < 0) {
        node->left = insert(node->left, student);
    } else if (strcmp(student.student_id, node->data.student_id) > 0) {
        node->right = insert(node->right, student);
    } else {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    if (balance > 1 && strcmp(student.student_id, node->left->data.student_id) < 0) {
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(student.student_id, node->right->data.student_id) > 0) {
        return leftRotate(node);
    }
    if (balance > 1 && strcmp(student.student_id, node->left->data.student_id) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(student.student_id, node->right->data.student_id) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::insert(const Student& student) {
    root = insert(root, student);
}

Node* AVLTree::deleteNode(Node* node, const char* student_id) {
    if (!node) return nullptr;
    if (strcmp(student_id, node->data.student_id) < 0) {
        node->left = deleteNode(node->left, student_id);
    } else if (strcmp(student_id, node->data.student_id) > 0) {
        node->right = deleteNode(node->right, student_id);
    } else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.student_id);
        }
    }
    if (!node) return nullptr;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rightRotate(node);
    }
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return leftRotate(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::deleteStudent(const char* student_id) {
    root = deleteNode(root, student_id);
}

Student* AVLTree::find(const char* student_id) {
    Node* result = find(root, student_id);
    return result ? &result->data : nullptr;
}

Node* AVLTree::find(Node* node, const char* student_id) {
    if (!node) return nullptr;
    if (strcmp(student_id, node->data.student_id) == 0) {
        return node;
    } else if (strcmp(student_id, node->data.student_id) < 0) {
        return find(node->left, student_id);
    } else {
        return find(node->right, student_id);
    }
}

void AVLTree::printTreeHelper(Node* root, const std::string& prefix, bool isLeft) {
    if (root != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );

        std::cout << root->data << std::endl;

        printTreeHelper(root->left, prefix + (isLeft ? "│   " : "    "), true);
        printTreeHelper(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

void AVLTree::print() {
    printTreeHelper(root, "", false);
}

void AVLTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void AVLTree::clear() {
    clear(root);
    root = nullptr;
}
