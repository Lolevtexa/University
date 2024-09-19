#pragma once

#include "../String/String.hpp"


class TextNode
{
public:
    String data;

    TextNode *next = nullptr;

public:
    TextNode();
    TextNode(String);
    TextNode(const TextNode &);

    ~TextNode();


    TextNode operator=(const TextNode &);
};
