#pragma once
#include <iostream>

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(const T& data, Node* next): data(data), next(next) {}

        ~Node()
        {
            delete next;
        }
    };

    Node* head;
    Node* tail;
    int length;

public:
    List(): head(nullptr), tail(nullptr), length(0) {}

    void push_back(const T& data)
    {
        Node* newNode = new Node(data, nullptr);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        length++;
    }

    void push_front(const T& data)
    {
        Node* newNode = new Node(data, head);

        if (head == nullptr)
        {
            tail = newNode;
        }

        head = newNode;
        length++;
    }

    void pop_back()
    {
        if (empty())
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        Node* temp = head;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            while (temp->next != tail)
            {
                temp = temp->next;
            }

            delete tail;
            tail = temp;
            tail->next = nullptr;
        }

        length--;
    }

    void pop_front()
    {
        if (empty())
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;

        length--;
    }

    void insert(int index, const T& data)
    {
        if (index < 0 || index > length)
        {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        if (index == 0)
        {
            push_front(data);
            return;
        }

        if (index == length)
        {
            push_back(data);
            return;
        }

        Node* temp = head;
        Node* newNode = new Node(data, nullptr);

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;

        length++;
    }

    void erase(int index)
    {
        if (index < 0 || index >= length)
        {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        if (index == 0)
        {
            pop_front();
            return;
        }

        if (index == length - 1)
        {
            pop_back();
            return;
        }

        Node* temp = head;
        Node* toDelete;

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        toDelete = temp->next;
        temp->next = toDelete->next;
        toDelete->next = nullptr;
        delete toDelete;

        length--;
    }

    T& operator[](int index) const
    {
        if (index < 0 || index >= length)
        {
            std::cout << "Invalid index" << std::endl;
            return tail->data;
        }

        Node* temp = head;

        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }

        return temp->data;
    }

    void clear()
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    int size() const
    {
        return length;
    }

    bool empty() const
    {
        return length == 0;
    }

    ~List()
    {
        delete head;
    }
};
