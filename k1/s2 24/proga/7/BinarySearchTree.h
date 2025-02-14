#pragma once
#include <iostream>

class BinarySearchTree
{
private:
    struct Node
    {
        int data;
        Node* left;
        Node* right;

        Node(int data, Node* left, Node* right):
            data(data),
            left(left),
            right(right)
        {}

        ~Node()
        {
            delete left;
            delete right;
        }
    };

    Node* root;

    void insert(Node*& node, int data)
    {
        if (node == nullptr)
        {
            node = new Node(data, nullptr, nullptr);
        }
        else if (data < node->data)
            insert(node->left, data);
        else
            insert(node->right, data);
    
    }

    bool find(Node* node, int data)
    {
        if (node == nullptr)
            return false;
        else if (data == node->data)
            return true;
        else if (data < node->data)
            return find(node->left, data);
        else
            return find(node->right, data);
    }

    void printHelper(int level, Node* node, int mode, char* modes) const
    {
        if (node == nullptr)
            return;

        modes[level + 1] = 'r';
        printHelper(level + 1, node->right, 1, modes);
        modes[level] = (mode == 0) ? 'm' : (mode == 1) ? 'v' : 'l';

        for (int i = 0; i < level; i++)
            if (modes[i] == 'v')
                std::cout << "│ ";
            else
                std::cout << "  ";

        switch (mode)    
        {
        case 1:
            std::cout << "┌─";
            break;

        case 0:
            std::cout << "├─";
            break;
        
        case -1:
            std::cout << "└─";
            break;
        }

        std::cout << node->data << std::endl;

        modes[level + 1] = 'v';
        printHelper(level + 1, node->left, -1, modes);
    }

    int height(Node* node) const
    {
        if (node == nullptr)
            return 0;
        else
        {
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
        }
    }

    void preOrder(Node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node* node) const
    {
        if (node == nullptr)
            return;

        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) const
    {
        if (node == nullptr)
            return;

        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << " ";
    }

    void clear(Node* node)
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    void insert(int data)
    {
        insert(root, data);
    }

    bool find(int data)
    {
        return find(root, data);
    }

    void print() const
    {
        int h = height(root);
        char *modes = new char[h + 1];

        modes[0] = 'm';
        for (int i = 1; i < h + 1; i++)
            modes[i] = 'v';

        printHelper(0, root, 0, modes);

        delete[] modes;
    }

    void preOrder() const
    {
        preOrder(root);
    }

    void inOrder() const
    {
        inOrder(root);
    }

    void postOrder() const
    {
        postOrder(root);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    ~BinarySearchTree()
    {
        delete root;
    }
};