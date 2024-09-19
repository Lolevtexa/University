#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
struct BSNode
{
    T data;

    BSNode *left;
    BSNode *right;
    BSNode *parent;
    
    BSNode(const T &data): 
        data(data),
        left(nullptr),
        right(nullptr),
        parent(nullptr)
    {}
};

template <typename T>
class BST
{
private:
    BSNode<T> *root;

    void insertNodeHelper(BSNode<T> *&node, const T &data, BSNode<T> *parent);
    BSNode<T> *searchHelper(BSNode<T> *node, const T &data);

    void deleteNodeHelper(BSNode<T> *&node, const T &data);
    void deleteTree(BSNode<T> *node);

    void BFSHelper(std::vector<BSNode<T> *> nodes) const;
    void DFSHelper(BSNode<T> *node) const;

    void inorderHelper(BSNode<T> *node) const;
    void preorderHelper(BSNode<T> *node) const;
    void postorderHelper(BSNode<T> *node) const;

    void printHelper(int level, BSNode<T> *node, int mode, char *modes) const;
    int height(BSNode<T> *node) const;

public:
    BST() : root(nullptr) {}
    ~BST() { deleteTree(root); }

    void insert(const T &data);
    void remove(const T &data);
    BSNode<T> *search(const T &data);

    void BFS() const;
    void DFS() const;

    void inorder() const;
    void preorder() const;
    void postorder() const;

    void print() const;

    int getSize() const;
    int getHeight() const;
};

template <typename T>
void BST<T>::insertNodeHelper(BSNode<T> *&node, const T &data, BSNode<T> *parent)
{
    if (node == nullptr)
    {
        node = new BSNode<T>(data);
        node->parent = parent;
        return;
    }

    if (data < node->data)
        insertNodeHelper(node->left, data, node);
    else if (data > node->data)
        insertNodeHelper(node->right, data, node);
}

template <typename T>
void BST<T>::deleteNodeHelper(BSNode<T> *&node, const T &data)
{
    if (node == nullptr)
        return;

    if (data < node->data)
        deleteNodeHelper(node->left, data);
    else if (data > node->data)
        deleteNodeHelper(node->right, data);
    else if (node->left == nullptr && node->right == nullptr)
    {
        if (node->parent != nullptr)
            if (node->parent->left == node) 
                node->parent->left = nullptr;
            else 
                node->parent->right = nullptr;
        else
            root = nullptr;

        delete node;
    }
    else if (node->left == nullptr) 
    {
        BSNode<T> *temp = node;
        node = node->right;
        node->parent = temp->parent;

        if (temp->parent != nullptr)
            if (temp->parent->left == temp)
                temp->parent->left = node;
            else
                temp->parent->right = node;
        else
            root = node;


        delete temp;
    } 
    else if (node->right == nullptr)
    {
        BSNode<T> *temp = node;
        node = node->left;
        node->parent = temp->parent;

        if (temp->parent != nullptr)
            if (temp->parent->left == temp)
                temp->parent->left = node;
            else
                temp->parent->right = node;
        
        else
            root = node;

        delete temp;
    } 
    else
    {
        BSNode<T> *temp = node->right;
        while (temp->left != nullptr)
            temp = temp->left;

        node->data = temp->data;
        deleteNodeHelper(node->right, temp->data);
    }
}

template <typename T>
BSNode<T> *BST<T>::searchHelper(BSNode<T> *node, const T &data) 
{
    if (node == nullptr || node->data == data)
        return node;

    if (data < node->data) 
    {
        if (node->left != nullptr)
            node->left->parent = node;
            
        return searchHelper(node->left, data);
    }
    if (node->right != nullptr)
        node->right->parent = node;
        
    return searchHelper(node->right, data);
}

template <typename T>
void BST<T>::deleteTree(BSNode<T> *node) 
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

template <typename T>
void BST<T>::BFSHelper(std::vector<BSNode<T> *> nodes) const
{
    if (!nodes.size())
        return;

    std::vector<BSNode<T> *> next;
    for (BSNode<T> *node : nodes)
    {
        std::cout << node->data << " ";

        if (node->left != nullptr)
            next.push_back(node->left);
        if (node->right != nullptr)
            next.push_back(node->right);
    }

    BFSHelper(next);
}

template <typename T>
void BST<T>::DFSHelper(BSNode<T> *node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    DFSHelper(node->left);
    DFSHelper(node->right);
}

template <typename T>
void BST<T>::inorderHelper(BSNode<T> *node) const
{
    if (node == nullptr)
        return;

    inorderHelper(node->left);
    std::cout << node->data << " ";
    inorderHelper(node->right);
}

template <typename T>
void BST<T>::preorderHelper(BSNode<T> *node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    preorderHelper(node->left);
    preorderHelper(node->right);
}

template <typename T>
void BST<T>::postorderHelper(BSNode<T> *node) const
{
    if (node == nullptr)
        return;

    postorderHelper(node->left);
    postorderHelper(node->right);
    std::cout << node->data << " ";
}

template <typename T>
void BST<T>::printHelper(int level, BSNode<T> *node, int mode, char *modes) const
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

template <typename T>
int BST<T>::height(BSNode<T> *node) const
{
    if (node == nullptr)
        return 0;
        
    return std::max(height(node->left), height(node->right)) + 1;
}

template <typename T>
void BST<T>::insert(const T &data)
{
    insertNodeHelper(root, data, nullptr);
}

template <typename T>
void BST<T>::remove(const T &data)
{
    deleteNodeHelper(root, data);
}

template <typename T>
BSNode<T> *BST<T>::search(const T &data) 
{
    return searchHelper(root, data);
}

template <typename T>
void BST<T>::BFS() const
{
    std::vector<BSNode<T> *> nodes;
    nodes.push_back(root);
    BFSHelper(nodes);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::DFS() const
{
    DFSHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::inorder() const
{
    inorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::preorder() const
{
    preorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::postorder() const
{
    postorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::print() const
{
    int h = height(root);
    char *modes = new char[h + 1];

    modes[0] = 'm';
    for (int i = 1; i < h + 1; i++)
        modes[i] = 'v';

    printHelper(0, root, 0, modes);

    delete[] modes;
}

template <typename T>
int BST<T>::getSize() const
{
    int size = 0;
    std::vector<BSNode<T> *> queue = {root};
    while (!queue.empty())
    {
        std::vector<BSNode<T> *> next;
        for (BSNode<T> *node : queue)
        {
            size++;
            if (node->left != nullptr)
                next.push_back(node->left);
            if (node->right != nullptr)
                next.push_back(node->right);
        }

        queue = next;
    }

    return size;
}

template <typename T>
int BST<T>::getHeight() const
{
    return height(root) - 1;
}
