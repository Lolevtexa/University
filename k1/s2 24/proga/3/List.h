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

        ~Node() {}
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
        tail->next = head;

        length++;
    }

    void push_front(const T& data)
    {
        Node* newNode = new Node(data, nullptr);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        tail->next = head;

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
        Node* toDelete = tail;

        while (temp->next != tail)
        {
            temp = temp->next;
        }

        tail = temp;
        tail->next = head;
        delete toDelete;

        length--;
    }

    void pop_front()
    {
        if (empty())
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        Node* toDelete = head;
        head = head->next;
        tail->next = head;
        delete toDelete;

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
        if (empty())
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

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

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        Node* toDelete = temp->next;
        temp->next = toDelete->next;

        delete toDelete;
        length--;
    }

    T& operator[](int index) const
    {
        if (empty())
        {
            throw std::out_of_range("List is empty");
        }

        if (index < 0 || index >= length)
        {
            throw std::out_of_range("Invalid index");
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
        if (head == nullptr)
        {
            return;
        }

        tail->next = nullptr;
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }

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
        clear();
    }
};
