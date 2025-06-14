#pragma once
#include <iostream>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();
    void insert(int value);
    void printPreOrder() const;
    void printInOrder() const;
    void printPostOrder() const;

private:
    TreeNode* root;
    void insertHelper(TreeNode*& node, int value);
    void printPreOrderHelper(TreeNode* node) const;
    void printInOrderHelper(TreeNode* node) const;
    void printPostOrderHelper(TreeNode* node) const;
    void clearHelper(TreeNode*& node);
};
