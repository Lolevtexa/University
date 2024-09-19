#pragma once
#include "Node.h"


class List
{
    Node *head = nullptr;
    
public:
    List();
    List(const List &);

    ~List();
    
    List operator=(const List &);

    void push_back(const int &data);
    void push_front(const int &data);
    void push_before_index(const int &data, const int &index);

    void pop_back();
    void pop_front();
    void pop_by_index(const int &index);

    void push_list_back(const List &list);
    void push_list_front(const List &list);
    void push_list_before_index(const List &list, const int &index);

    void clear();
    bool is_clear();

    bool in(const List &list);
    int find_first_inclusion(const List &list);
    int find_last_inclusion(const List &list);

    int get(const int &index);
    void set(const int &data, const int &index);

    int size();

    void reverse();
    void permutation(List &list, const int &index1, const int &index2);

    void print(int i);
};