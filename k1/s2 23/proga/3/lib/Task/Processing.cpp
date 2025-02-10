#include "Task.hpp"

void Processing(List &list, String v1, String v2)
{
    if (haveErrors)
        return;

    for (int i = 0; i < list.Size(); i++)
        if (list[i] == v1)
            list.Insert(v2, i++);
}