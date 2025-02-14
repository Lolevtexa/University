#include "List.h"


List::List()
{
}

List::List(const List &list)
{
    if (list.head != nullptr)
    {
        head = new Node(*list.head);
        
        Node *cur = head;
        while (cur->next != nullptr)
            cur = cur->next;
    }
}


List::~List()
{
    if (head != nullptr)
        delete head;

}


List List::operator=(const List &text)
{
    clear();
    if (text.head != nullptr)
    {
        head = new Node(*text.head);
    }
    return *this;
}


void List::push_back(const int &data)
{
    Node *new_node = new Node(data);

    if (head == nullptr)
    {
        head = new_node;
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
        current = current->next;

    current->next = new_node;
}

void List::push_front(const int &data)
{
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = head;

    head = new_node;
}

void List::push_before_index(const int &data, const int &index)
{
    if (index == 0)
    {
        push_front(data);
        return;
    }

    Node *new_node = new Node(data);

    Node *current = head;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    new_node->next = current->next;
    current->next = new_node;
}


void List::pop_back()
{
    if (head == nullptr)
        return;

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    Node *current = head;
    while (current->next->next != nullptr)
        current = current->next;

    delete current->next;
    current->next = nullptr;
}

void List::pop_front()
{
    if (head == nullptr)
        return;

    Node *temp = head;
    head = head->next;

    temp->next = nullptr;
    delete temp;
}

void List::pop_by_index(const int &index)
{
    if (index == 0)
    {
        pop_front();
        return;
    }

    Node *current = head;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    Node *temp = current->next;
    current->next = current->next->next;

    temp->next = nullptr;
    delete temp;
}


void List::push_list_back(const List &list)
{
    if (list.head == nullptr)
        return;
    
    if (head == nullptr)
    {
        head = new Node(*list.head);
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
        current = current->next;

    current->next = new Node(*list.head);
}

void List::push_list_front(const List &list)
{
    if (list.head == nullptr)
        return;

    if (head == nullptr)
    {
        *this = list;
        return;
    }

    Node *temp = head;
    head = new Node(*list.head);

    Node *current = head;
    while (current->next != nullptr)
        current = current->next;
    
    current->next = temp;
}

void List::push_list_before_index(const List &list, const int &index)
{
    if (list.head == nullptr)
        return;

    if (index == 0)
    {
        push_list_front(list);
        return;
    }

    Node *current = head;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    Node *temp = current->next;
    current->next = new Node(*list.head);

    Node *cur = current->next;
    while (cur->next != nullptr)
        cur = cur->next;

    cur->next = temp;
}



void List::clear()
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;

        temp->next = nullptr;
        delete temp;
    }
    
    head = nullptr;
}

bool List::is_clear()
{
    return head == nullptr;
}


bool List::in(const List &list)
{
    Node *current = head;
    while (current != nullptr)
    {
        bool is_in = true;

        Node *current_list = list.head;
        Node *current_current = current;
        while (current_list != nullptr && current_current != nullptr)
        {
            if (current_current->data != current_list->data)
            {
                is_in = false;
                break;
            }

            current_list = current_list->next;
            current_current = current_current->next;
        }
        

        if (is_in && current_list == nullptr)
            return true;

        current = current->next;
    }

    return false;
}

int List::find_first_inclusion(const List &list)
{
    Node *current = head;
    int index = 0;
    while (current != nullptr)
    {
        bool is_in = true;

        Node *current_list = list.head;
        Node *current_current = current;
        while (current_list != nullptr && current_current != nullptr)
        {
            if (current_current->data != current_list->data)
            {
                is_in = false;
                break;
            }

            current_list = current_list->next;
            current_current = current_current->next;
        }
        

        if (is_in && current_list == nullptr)
            return index;

        current = current->next;
        index++;
    }

    return -1;
}

int List::find_last_inclusion(const List &list)
{
    Node *current = head;
    int index = 0;
    int last_index = -1;
    while (current != nullptr)
    {
        bool is_in = true;

        Node *current_list = list.head;
        Node *current_current = current;
        while (current_list != nullptr && current_current != nullptr)
        {
            if (current_current->data != current_list->data)
            {
                is_in = false;
                break;
            }

            current_list = current_list->next;
            current_current = current_current->next;
        }
        

        if (is_in && current_list == nullptr)
            last_index = index;

        current = current->next;
        index++;
    }

    return last_index;
}


int List::get(const int &index)
{
    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;

    return current->data;
}

void List::set(const int &data, const int &index)
{
    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;

    current->data = data;
}


int List::size()
{
    int size = 0;
    Node *current = head;
    while (current != nullptr)
    {
        size++;
        current = current->next;
    }

    return size;
}


void List::reverse()
{
    int s = size();
    int list[s];
    Node *current = head;
    for (int i = 0; current != nullptr; i++)
    {
        list[i] = current->data;
        current = current->next;
    }

    current = head;
    for (int i = 0; i < s; i++) 
    {
        current->data = list[s - i - 1];
        current = current->next;
    }
}

void List::permutation(List &list, const int &index1, const int &index2)
{
    int temp = get(index1);
    set(list.get(index2), index1);
    list.set(temp, index2);
}


void List::print(int i)
{
    std::cout << i << ": ";
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
