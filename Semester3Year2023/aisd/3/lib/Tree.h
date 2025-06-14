#include "BST.h"
#include "AVLT.h"
#include "RBT.h"

enum Type { _BST, _AVLT, _RBT };

template <typename T>
struct TNode
{
    Type type;
    
    BSNode<T> *bst;
    AVLNode<T> *avlt;
    RBNode<T> *rbt;

    TNode(BSNode<T> *node)
    {
        type = Type::_BST;
        bst = node;
    }

    TNode(AVLNode<T> *node)
    {
        type = Type::_AVLT;
        avlt = node;
    }

    TNode(RBNode<T> *node)
    {
        type = Type::_RBT;
        rbt = node;
    }
};

template <typename T>
class Tree
{
private:
    Type type;

    BST<T> *bst;
    AVLT<T> *avlt;
    RBT<T> *rbt;

public:
    Tree() : bst(nullptr), avlt(nullptr), rbt(nullptr) {};
    Tree(Type type);
    ~Tree();

    void insert(const T &data);
    void remove(const T &data);
    TNode<T> *search(const T &data) const;

    void BFS() const;
    void DFS() const;

    void inorder() const;
    void preorder() const;
    void postorder() const;

    void print() const;

    int getSize() const;
    int getHeight() const;

    void setType(Type type);
};

template <typename T>
Tree<T>::Tree(Type type):
    type(type),
    bst(nullptr),
    avlt(nullptr),
    rbt(nullptr)
{
    switch (type)
    {
        case Type::_BST:
            bst = new BST<T>();
            break;
        case Type::_AVLT:
            avlt = new AVLT<T>();
            break;
        case Type::_RBT:
            rbt = new RBT<T>();
            break;
    }
}

template <typename T>
Tree<T>::~Tree() 
{
    switch (type)
    {
        case Type::_BST:
            delete bst;
            break;
        case Type::_AVLT:
            delete avlt;
            break;
        case Type::_RBT:
            delete rbt;
            break;
    }
}

template <typename T>
void Tree<T>::insert(const T &data) 
{
    switch (type)
    {
        case Type::_BST:
            bst->insert(data);
            break;
        case Type::_AVLT:
            avlt->insert(data);
            break;
        case Type::_RBT:
            rbt->insert(data);
            break;
    }
}

template <typename T>
void Tree<T>::remove(const T &data) 
{
    switch (type)
    {
        case Type::_BST:
            bst->remove(data);
            break;
        case Type::_AVLT:
            avlt->remove(data);
            break;
        case Type::_RBT:
            rbt->remove(data);
            break;
    }
}

template <typename T>
TNode<T> *Tree<T>::search(const T &data) const 
{
    switch (type)
    {
        case Type::_BST:
            return new TNode(bst->search(data));
        case Type::_AVLT:
            return new TNode(avlt->search(data));
        case Type::_RBT:
            return new TNode(rbt->search(data));
    }
    return nullptr;
}

template <typename T>
void Tree<T>::BFS() const 
{
    switch (type)
    {
        case Type::_BST:
            bst->BFS();
            break;
        case Type::_AVLT:
            avlt->BFS();
            break;
        case Type::_RBT:
            rbt->BFS();
            break;
    }
}

template <typename T>
void Tree<T>::DFS() const 
{
    switch (type)
    {
        case Type::_BST:
            bst->DFS();
            break;
        case Type::_AVLT:
            avlt->DFS();
            break;
        case Type::_RBT:
            rbt->DFS();
            break;
    }
}

template <typename T>
void Tree<T>::inorder() const 
{
    switch (type)
    {
        case Type::_BST:
            bst->inorder();
            break;
        case Type::_AVLT:
            avlt->inorder();
            break;
        case Type::_RBT:
            rbt->inorder();
            break;
    }
}

template <typename T>
void Tree<T>::preorder() const 
{
    switch (type)
    {
        case Type::_BST:
            bst->preorder();
            break;
        case Type::_AVLT:
            avlt->preorder();
            break;
        case Type::_RBT:
            rbt->preorder();
            break;
    }
}

template <typename T>
void Tree<T>::postorder() const 
{
    switch (type)
    {
        case Type::_BST:
            bst->postorder();
            break;
        case Type::_AVLT:
            avlt->postorder();
            break;
        case Type::_RBT:
            rbt->postorder();
            break;
    }
}

template <typename T>
void Tree<T>::print() const 
{
    switch (type)
    {
        case Type::_BST:
            bst->print();
            break;
        case Type::_AVLT:
            avlt->print();
            break;
        case Type::_RBT:
            rbt->print();
            break;
    }
}

template <typename T>
int Tree<T>::getSize() const 
{
    switch (type)
    {
        case Type::_BST:
            return bst->getSize();
        case Type::_AVLT:
            return avlt->getSize();
        case Type::_RBT:
            return rbt->getSize();
    }
    return 0;
}

template <typename T>
int Tree<T>::getHeight() const 
{
    switch (type)
    {
        case Type::_BST:
            return bst->getHeight();
        case Type::_AVLT:
            return avlt->getHeight();
        case Type::_RBT:
            return rbt->getHeight();
    }
    return 0;
}

template <typename T>
void Tree<T>::setType(Type type)
{
    this->type = type;
    switch (type)
    {
        case Type::_BST:
            bst = new BST<T>();
            break;
        case Type::_AVLT:
            avlt = new AVLT<T>();
            break;
        case Type::_RBT:
            rbt = new RBT<T>();
            break;
    }
}