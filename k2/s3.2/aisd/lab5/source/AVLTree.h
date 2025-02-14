#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Student.h"

struct Node {
    Student data;
    Node* left;
    Node* right;
    int height;

    Node(const Student& student);
};

class AVLTree {
private:
    Node* root;

    Node* insert(Node* node, const Student& student);
    Node* deleteNode(Node* node, const char* student_id);
    Node* find(Node* node, const char* student_id);
    void clear(Node* node);
    void printTreeHelper(Node* node, const std::string& prefix, bool isLeft);
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);
    Node* minValueNode(Node* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(const Student& student);
    void deleteStudent(const char* student_id);
    Student* find(const char* student_id);
    void print();
    void clear();
};

#endif // AVL_TREE_H
