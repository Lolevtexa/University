#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
struct AVLNode
{
    T data;

    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

    int height;

    AVLNode(const T &data): 
        data(data), 
        height(1),
        left(nullptr),
        right(nullptr),
        parent(nullptr)
    {}
};

template <typename T>
class AVLT
{
private:
    AVLNode<T> *root;

    int height(AVLNode<T> *) const;
    int balanceFactor(AVLNode<T> *) const;
    void fixHeight(AVLNode<T> *);

    AVLNode<T> *rotateLeft(AVLNode<T> *);
    AVLNode<T> *rotateRight(AVLNode<T> *);
 
    AVLNode<T> *insertNodeHelper(AVLNode<T> *, const T &, AVLNode<T> *);
    AVLNode<T> *balance(AVLNode<T> *);

    void deleteTree(AVLNode<T> *);
    AVLNode<T> *deleteNodeHelper(AVLNode<T> *, const T &);
    AVLNode<T> *deleteMin(AVLNode<T> *);

    AVLNode<T> *minimumNode(AVLNode<T> *) const;
    AVLNode<T> *maximumNode(AVLNode<T> *) const;
    AVLNode<T> *searchHelper(AVLNode<T> *, const T &) const;

    void BFSHelper(std::vector<AVLNode<T> *>) const;
    void DFSHelper(AVLNode<T> *) const;

    void inorderHelper(AVLNode<T> *) const;
    void preorderHelper(AVLNode<T> *) const;
    void postorderHelper(AVLNode<T> *) const;

    void printHelper(int, AVLNode<T> *, int, char *) const;

public:
    AVLT() : root(nullptr) {}
    ~AVLT() { deleteTree(root); }

    void insert(const T &data);
    void remove(const T &data);
    AVLNode<T> *search(const T &data);

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
int AVLT<T>::height(AVLNode<T> *node) const
{
    if (node == nullptr)
        return 0;
        
    return node->height;
}

template <typename T>
int AVLT<T>::balanceFactor(AVLNode<T> *node) const
{
    if (node == nullptr)
        return 0;
        
    return height(node->right) - height(node->left);
}

template <typename T>
void AVLT<T>::fixHeight(AVLNode<T> *node) 
{
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template <typename T>
AVLNode<T> *AVLT<T>::rotateRight(AVLNode<T> *node) 
{
    AVLNode<T> *left = node->left;
    node->left = left->right;

    if (left->right != nullptr)
        left->right->parent = node;

    left->right = node;
    left->parent = node->parent;
    node->parent = left;

    fixHeight(node);
    fixHeight(left);

    return left;
}

template <typename T>
AVLNode<T> *AVLT<T>::rotateLeft(AVLNode<T> *node)
{
    AVLNode<T> *right = node->right;
    node->right = right->left;
    if (right->left != nullptr)
        right->left->parent = node;
        
    right->left = node;
    right->parent = node->parent;
    node->parent = right;
    
    fixHeight(node);
    fixHeight(right);
    
    return right;
}

template <typename T>
AVLNode<T> *AVLT<T>::balance(AVLNode<T> *node) 
{
    fixHeight(node);

    if (balanceFactor(node) == 2) 
    {
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);

        return rotateLeft(node);
    }

    if (balanceFactor(node) == -2) 
    {
        if (balanceFactor(node->left) > 0) 
            node->left = rotateLeft(node->left);

        return rotateRight(node);
    }

    return node;
}

template <typename T>
AVLNode<T> *AVLT<T>::insertNodeHelper(AVLNode<T> *node, const T &data, AVLNode<T> *parent) 
{
    if (node == nullptr) 
        return new AVLNode<T>(data);

    if (data < node->data)
        node->left = insertNodeHelper(node->left, data, node);
    else
        node->right = insertNodeHelper(node->right, data, node);

    return balance(node);
}

template <typename T>
AVLNode<T> *AVLT<T>::minimumNode(AVLNode<T> *node) const
{
    if (node->left == nullptr)
        return node;

    return minimumNode(node->left);
}

template <typename T>
AVLNode<T> *AVLT<T>::maximumNode(AVLNode<T> *node) const
{
    if (node->right == nullptr)
        return node;

    return maximumNode(node->right);
}

template <typename T>
AVLNode<T> *AVLT<T>::deleteMin(AVLNode<T> *node) 
{
    if (node->left == nullptr)
        return node->right;

    node->left = deleteMin(node->left);
    return balance(node);
}

template <typename T>
void AVLT<T>::deleteTree(AVLNode<T> *node) 
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

template <typename T>
AVLNode<T> *AVLT<T>::deleteNodeHelper(AVLNode<T> *node, const T &data) 
{
    if (node == nullptr)
        return nullptr;
        
    if (data < node->data)
        node->left = deleteNodeHelper(node->left, data);
    else if (data > node->data)
        node->right = deleteNodeHelper(node->right, data);
    else 
    {
        AVLNode<T> *left = node->left;
        AVLNode<T> *right = node->right;
        AVLNode<T> *parent = node->parent;
        delete node;
        if (right == nullptr) 
        {
            if (left != nullptr)
                left->parent = parent;

            return left;
        }
        AVLNode<T> *min = minimumNode(right);
        min->right = deleteMin(right);
        min->left = left;
        min->parent = parent;
        if (left != nullptr)
            left->parent = min;
    
        return balance(min);
    }
    return balance(node);
}

template <typename T>
AVLNode<T> *AVLT<T>::searchHelper(AVLNode<T> *node, const T &data) const 
{
    if (node == nullptr || node->data == data)
        return node;

    if (data < node->data)
        return searchHelper(node->left, data);
        
    return searchHelper(node->right, data);
}

template <typename T>
void AVLT<T>::BFSHelper(std::vector<AVLNode<T> *> queue) const
{
    if (queue.empty())
        return;

    std::vector<AVLNode<T>*> next;
    for (AVLNode<T> *node : queue)
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
void AVLT<T>::DFSHelper(AVLNode<T> *node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    DFSHelper(node->left);
    DFSHelper(node->right);
}

template <typename T>
void AVLT<T>::inorderHelper(AVLNode<T> *node) const
{
    if (node == nullptr)
        return;

    inorderHelper(node->left);
    std::cout << node->data << " ";
    inorderHelper(node->right);
}

template <typename T>
void AVLT<T>::preorderHelper(AVLNode<T> *node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    preorderHelper(node->left);
    preorderHelper(node->right);
}

template <typename T>
void AVLT<T>::postorderHelper(AVLNode<T> *node) const
{
    if (node == nullptr)
        return;

    postorderHelper(node->left);
    postorderHelper(node->right);
    std::cout << node->data << " ";
}

template <typename T>
void AVLT<T>::printHelper(int level, AVLNode<T> *node, int mode, char *modes) const
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
void AVLT<T>::insert(const T &data) 
{
    root = insertNodeHelper(root, data, nullptr);
}

template <typename T>
void AVLT<T>::remove(const T &data) 
{
    root = deleteNodeHelper(root, data);
}
template <typename T>
AVLNode<T> *AVLT<T>::search(const T &data) 
{
    return searchHelper(root, data);
}

template <typename T>
void AVLT<T>::BFS() const
{
    BFSHelper({root});
    std::cout << std::endl;
}

template <typename T>
void AVLT<T>::DFS() const
{
    DFSHelper(root);
    std::cout << std::endl;
}

template <typename T>
void AVLT<T>::inorder() const
{
    inorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void AVLT<T>::preorder() const
{
    preorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void AVLT<T>::postorder() const
{
    postorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void AVLT<T>::print() const
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
int AVLT<T>::getSize() const
{
    int size = 0;
    std::vector<AVLNode<T> *> queue = {root};
    while (!queue.empty())
    {
        std::vector<AVLNode<T> *> next;
        for (AVLNode<T> *node : queue)
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
int AVLT<T>::getHeight() const
{
    return height(root);
}
