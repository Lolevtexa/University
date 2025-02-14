#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

enum Color { RED, BLACK };

template <typename T>
struct RBNode
{
public:
    T data;
    Color color;

    RBNode *left;
    RBNode *right;
    RBNode *parent;

    RBNode(const T &data): 
        data(data),
        color(RED),
        left(nullptr),
        right(nullptr),
        parent(nullptr) 
    {}
};

template <typename T>
class RBT
{
private:
    RBNode<T> *root;

    void rotateLeft(RBNode<T> *&);
    void rotateRight(RBNode<T> *&);
    void fixViolation(RBNode<T> *&);

    RBNode<T> *minimumNode(RBNode<T> *) const;
    RBNode<T> *maximumNode(RBNode<T> *) const;
    RBNode<T> *searchHelper(RBNode<T> *, const T &) const;

    void deleteTree(RBNode<T>*);
    void deleteNodeHelper(RBNode<T>*, const T &);
    void fixDoubleBlack(RBNode<T>*);

    void BFSHelper(std::vector<RBNode<T> *>) const;
    void DFSHelper(RBNode<T> *) const;

    void inorderHelper(RBNode<T> *) const;
    void preorderHelper(RBNode<T> *) const;
    void postorderHelper(RBNode<T> *) const;

    void printHelper(int, RBNode<T> *, int, char *) const;
    int height(RBNode<T> *node) const;

public:
    RBT() : root(nullptr) {}
    ~RBT() { deleteTree(root); }

    void insert(const T&);
    void remove(const T&);
    RBNode<T> *search(const T&);

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
void RBT<T>::rotateLeft(RBNode<T> *&ptr)
{
    RBNode<T> *rightChild = ptr->right;
    ptr->right = rightChild->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    rightChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = rightChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = rightChild;
    else
        ptr->parent->right = rightChild;

    rightChild->left = ptr;
    ptr->parent = rightChild;
}

template <typename T>
void RBT<T>::rotateRight(RBNode<T> *&ptr)
{
    RBNode<T> *leftChild = ptr->left;
    ptr->left = leftChild->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    leftChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = leftChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = leftChild;
    else
        ptr->parent->right = leftChild;

    leftChild->right = ptr;
    ptr->parent = leftChild;
}

template <typename T>
void RBT<T>::fixViolation(RBNode<T> *&ptr)
{
    RBNode<T> *parentPtr = nullptr;
    RBNode<T> *grandParentPtr = nullptr;

    while ((ptr != root) && (ptr->color != BLACK) && (ptr->parent->color == RED))
    {
        parentPtr = ptr->parent;
        grandParentPtr = ptr->parent->parent;

        if (parentPtr == grandParentPtr->left)
        {
            RBNode<T> *unclePtr = grandParentPtr->right;

            if (unclePtr != nullptr && unclePtr->color == RED)
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                ptr = grandParentPtr;
            }
            else
            {
                if (ptr == parentPtr->right)
                {
                    rotateLeft(parentPtr);
                    ptr = parentPtr;
                    parentPtr = ptr->parent;
                }

                rotateRight(grandParentPtr);
                std::swap(parentPtr->color, grandParentPtr->color);
                ptr = parentPtr;
            }
        }
        else
        {
            RBNode<T> *unclePtr = grandParentPtr->left;

            if ((unclePtr != nullptr) && (unclePtr->color == RED))
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                ptr = grandParentPtr;
            }
            else
            {
                if (ptr == parentPtr->left)
                {
                    rotateRight(parentPtr);
                    ptr = parentPtr;
                    parentPtr = ptr->parent;
                }

                rotateLeft(grandParentPtr);
                std::swap(parentPtr->color, grandParentPtr->color);
                ptr = parentPtr;
            }
        }
    }

    root->color = BLACK;
}

template <typename T>
void RBT<T>::insert(const T &data)
{
    RBNode<T> *newNode = new RBNode<T>(data);
    if (root == nullptr)
    {
        newNode->color = BLACK;
        root = newNode;
    }
    else
    {
        RBNode<T> *ptr = root;
        RBNode<T> *parentPtr = nullptr;

        while (ptr != nullptr)
        {
            parentPtr = ptr;

            if (newNode->data < ptr->data)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }

        newNode->parent = parentPtr;

        if (newNode->data < parentPtr->data)
            parentPtr->left = newNode;
        else
            parentPtr->right = newNode;

        fixViolation(newNode);
    }
}

template <typename T>
void RBT<T>::BFSHelper(std::vector<RBNode<T> *> queue) const
{
    if (queue.empty())
        return;

    std::vector<RBNode<T>*> nextQueue;
    for (auto node : queue)
    {
        std::cout << node->data << " ";
        if (node->left != nullptr)
            nextQueue.push_back(node->left);

        if (node->right != nullptr)
            nextQueue.push_back(node->right);
    }

    BFSHelper(nextQueue);
}

template <typename T>
void RBT<T>::DFSHelper(RBNode<T> *ptr) const
{
    if (ptr == nullptr)
        return;

    std::cout << ptr->data << " ";
    DFSHelper(ptr->left);
    DFSHelper(ptr->right);
}

template <typename T>
void RBT<T>::inorderHelper(RBNode<T> *ptr) const
{
    if (ptr == nullptr)
        return;

    inorderHelper(ptr->left);
    std::cout << ptr->data << " ";
    inorderHelper(ptr->right);
}

template <typename T>
void RBT<T>::preorderHelper(RBNode<T> *ptr) const
{
    if (ptr == nullptr)
        return;

    std::cout << ptr->data << " ";
    preorderHelper(ptr->left);
    preorderHelper(ptr->right);
}

template <typename T>
void RBT<T>::postorderHelper(RBNode<T> *ptr) const
{
    if (ptr == nullptr)
        return;

    postorderHelper(ptr->left);
    postorderHelper(ptr->right);
    std::cout << ptr->data << " ";
}

template <typename T>
void RBT<T>::printHelper(int level, RBNode<T> *node, int mode, char *modes) const
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

    std::cout << (node->color == RED ? 'r' : 'b') << node->data << ' ' << std::endl;

    modes[level + 1] = 'v';
    printHelper(level + 1, node->left, -1, modes);
}

template <typename T>
RBNode<T> *RBT<T>::minimumNode(RBNode<T> *ptr) const
{
    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

template <typename T>
RBNode<T> *RBT<T>::maximumNode(RBNode<T> *ptr) const
{
    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

template <typename T>
RBNode<T> *RBT<T>::searchHelper(RBNode<T> *ptr, const T &data) const
{
    if (ptr == nullptr || ptr->data == data)
        return ptr;

    if (data < ptr->data)
        return searchHelper(ptr->left, data);

    return searchHelper(ptr->right, data);
}

template <typename T>
void RBT<T>::deleteTree(RBNode<T> *ptr)
{
    if (ptr == nullptr)
        return;

    deleteTree(ptr->left);
    deleteTree(ptr->right);
    delete ptr;
}

template <typename T>
void RBT<T>::deleteNodeHelper(RBNode<T> *ptr, const T &data)
{
    RBNode<T> *z = nullptr;
    RBNode<T> *x, *y;
    while (ptr != nullptr)
    {
        if (ptr->data == data)
            z = ptr;

        if (ptr->data <= data)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }

    if (z == nullptr)
        return;

    if (z->left == nullptr && z->right == nullptr)
    {
        y = nullptr;
    }
    else if (z->left == nullptr || z->right == nullptr)
    {
        y = z->right == nullptr ? z->left : z->right;
        y->parent = z->parent;
    }
    else
    {
        y = minimumNode(z->right);
        z->data = y->data;
        deleteNodeHelper(y, y->data);
        return;
    }

    if (z->color == BLACK)
        fixDoubleBlack(z);

    if (z->parent == nullptr)
        root = y;
    else if (z == z->parent->left)
        z->parent->left = y;
    else
        z->parent->right = y;

    delete z;
}

template <typename T>
void RBT<T>::fixDoubleBlack(RBNode<T> *ptr)
{
    if (ptr == root)
        return;

    RBNode<T> *sibling = nullptr;
    RBNode<T> *parent = ptr->parent;
    if (ptr == parent->left)
        sibling = parent->right;
    else
        sibling = parent->left;

    if (sibling == nullptr)
        fixDoubleBlack(parent);
    else
    {
        if (sibling->color == RED)
        {
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling == parent->left)
                rotateRight(parent);
            else
                rotateLeft(parent);

            fixDoubleBlack(ptr);
        }
        else
        {
            if ((sibling->left != nullptr && sibling->left->color == RED) || 
                (sibling->right != nullptr && sibling->right->color == RED))
            {
                if (sibling->left != nullptr && sibling->left->color == RED)
                {
                    if (sibling == parent->left)
                    {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(parent);
                    }
                    else
                    {
                        sibling->left->color = parent->color;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                }
                else
                {
                    if (sibling == parent->left)
                    {
                        sibling->right->color = parent->color;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    }
                    else
                    {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(parent);
                    }
                }

                parent->color = BLACK;
            }
            else
            {
                sibling->color = RED;
                if (parent->color == BLACK)
                    fixDoubleBlack(parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}

template <typename T>
void RBT<T>::remove(const T &data)
{
    deleteNodeHelper(root, data);
}

template <typename T>
RBNode<T> *RBT<T>::search(const T &data)
{
    return searchHelper(root, data);
}

template <typename T>
void RBT<T>::BFS() const
{
    BFSHelper({root});
    std::cout << std::endl;
}

template <typename T>
void RBT<T>::DFS() const
{
    DFSHelper(root);
    std::cout << std::endl;
}

template <typename T>
void RBT<T>::inorder() const
{
    inorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void RBT<T>::preorder() const
{
    preorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void RBT<T>::postorder() const
{
    postorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void RBT<T>::print() const
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
int RBT<T>::height(RBNode<T> *node) const
{
    if (node == nullptr)
        return 1;
        
    return std::max(height(node->left), height(node->right)) + 1;
}

template <typename T>
int RBT<T>::getSize() const
{
    int size = 0;
    std::vector<RBNode<T> *> queue = {root};
    while (!queue.empty())
    {
        std::vector<RBNode<T> *> next;
        for (RBNode<T> *node : queue)
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
int RBT<T>::getHeight() const
{
    return height(root);
}
