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
        Node* prev;

        Node(const T& data): data(data), next(nullptr), prev(nullptr) {}

        ~Node() {}

        Node(const Node& other) = delete;
        Node& operator=(const Node& other) = delete;
    };

    Node* head;
    Node* tail;
    int length;

public:
    List(): head(nullptr), tail(nullptr), length(0) {}

    void push_back(const T& data)
    {
        Node* newNode = new Node(data);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        length++;
    }

    void push_front(const T& data)
    {
        Node* newNode = new Node(data);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        length++;
    }
    
    void pop_back()
    {
        if (empty())
        {
            return;
        }

        Node* temp = tail;
        tail = tail->prev;
        delete temp;

        if (tail == nullptr)
        {
            head = nullptr;
        }
        else
        {
            tail->next = nullptr;
        }

        length--;
    }

    void pop_front()
    {
        if (empty())
        {
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr)
        {
            tail = nullptr;
        }
        else
        {
            head->prev = nullptr;
        }

        length--;
    }

    void insert(const T& data, int index)
    {
        if (index < 0 || index > length)
        {
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

        Node* newNode = new Node(data);
        Node* temp = head;

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;

        length++;
    }

    void erase(int index)
    {
        if (index < 0 || index >= length)
        {
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

        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;

        length--;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= length)
        {
            std::cout << "Invalid index" << std::endl;
            exit(1);
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
    
    bool operator==(const List<T>& other) const
    {
        if (length != other.length)
        {
            return false;
        }

        Node* current = head;
        Node* otherCurrent = other.head;

        while (current != nullptr)
        {
            if (current->data != otherCurrent->data)
            {
                return false;
            }

            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        return true;
    }

    bool operator!=(const List<T>& other) const
    {
        return !(*this == other);
    }

    List(const List<T>& other): head(nullptr), tail(nullptr), length(0)
    {
        Node* current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    List<T>& operator=(const List<T>& other)
    {
        if (this != &other)
        {
            clear();
            Node* current = other.head;
            while (current != nullptr)
            {
                push_back(current->data);
                current = current->next;
            }
        }

        return *this;
    }
};
