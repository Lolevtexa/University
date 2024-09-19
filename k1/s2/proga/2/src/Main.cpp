#include "../lib/Text/Text.h"

int main()
{
    Text start;
    start.Input();

    Text end = start.Processing();
    end.Output();

    return 0;
}