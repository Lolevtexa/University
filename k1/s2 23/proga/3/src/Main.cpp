#include "../lib/Task/Task.hpp"

int main()
{
    String v1, v2;
    List list = InputFromFile("files/input.txt", v1, v2);

    OutputToFile("files/output.txt", list, std::ios::out);
    
    Processing(list, v1, v2);
    
    OutputToFile("files/output.txt", list, std::ios::app);

    list.Delete();
    return 0;
}