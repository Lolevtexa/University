#pragma once
#include <iostream>

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node() : data(0), next(nullptr) {}

        Node(T data) : data(data), next(nullptr) {}

        ~Node()
        {
            delete next;
        }
    };

    Node* head;

public:
    Stack() : head(nullptr) {}

    void push(T data)
    {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    void pop()
    {
        if (empty())
        {
            std::cout << "Stack is empty" << std::endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
    }

    T top()
    {
        if (empty())
        {
            std::cout << "Stack is empty" << std::endl;
            return -1;
        }

        return head->data;
    }

    bool empty()
    {
        return head == nullptr;
    }

    ~Stack()
    {
        delete head;
    }
};
