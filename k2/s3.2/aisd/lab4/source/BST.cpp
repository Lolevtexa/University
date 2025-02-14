#include "BST.h"

BST::BST() : root(nullptr) {}

BST::~BST() {
    clearHelper(root);
}

void BST::insert(int value) {
    insertHelper(root, value);
}

void BST::insertHelper(TreeNode*& node, int value) {
    if (!node) {
        node = new TreeNode(value);
    } else if (value < node->value) {
        insertHelper(node->left, value);
    } else {
        insertHelper(node->right, value);
    }
}

void BST::printPreOrder() const {
    printPreOrderHelper(root);
    std::cout << std::endl;
}

void BST::printPreOrderHelper(TreeNode* node) const {
    if (node) {
        std::cout << node->value << " ";
        printPreOrderHelper(node->left);
        printPreOrderHelper(node->right);
    }
}

void BST::printInOrder() const {
    printInOrderHelper(root);
    std::cout << std::endl;
}

void BST::printInOrderHelper(TreeNode* node) const {
    if (node) {
        printInOrderHelper(node->left);
        std::cout << node->value << " ";
        printInOrderHelper(node->right);
    }
}

void BST::printPostOrder() const {
    printPostOrderHelper(root);
    std::cout << std::endl;
}

void BST::printPostOrderHelper(TreeNode* node) const {
    if (node) {
        printPostOrderHelper(node->left);
        printPostOrderHelper(node->right);
        std::cout << node->value << " ";
    }
}

void BST::clearHelper(TreeNode*& node) {
    if (node) {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = nullptr;
    }
}
