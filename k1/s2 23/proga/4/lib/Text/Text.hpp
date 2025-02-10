#pragma once

#include "../TextNode/TextNode.hpp"


class Text
{
private:
    TextNode *root = nullptr;

public:
    int size = 0;

public:
    Text();
    Text(const Text &);

    ~Text();

    
    void pushBack(String);
    
    void pushFront(String);


    void insert(String, int);

    void remove(int);

    
    String &operator[](int) const;
    Text operator=(const Text &);
};
