#include "lib/List.h"

int main()
{
    int i = 0;

    List list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(4);
    list.push_front(5);
    list.push_front(6);
    list.push_before_index(7, 0);
    list.push_before_index(8, 1);
    list.push_before_index(9, 2);

    list.print(++i); //1

    list.pop_back(); 
    
    list.print(++i); //2

    list.pop_front();
    
    list.print(++i); //3
    
    list.pop_by_index(0);
    
    list.print(++i); //4
    
    list.pop_by_index(1);
    
    list.print(++i); //5

    List list2;
    list2.push_back(10);
    list2.push_back(11);
    list2.push_back(12);
    list2.push_front(13);
    list2.push_front(14);
    list2.push_front(15);
    list2.push_before_index(16, 0);
    list2.push_before_index(17, 1);
    list2.push_before_index(18, 2);

    list2.print(++i); //6
 
    list.push_list_back(list2);

    list.print(++i); //7

    // list2.clear();

    list2.print(++i); //8
    list.print(++i); //9

    list.push_list_front(list2);
    
    list.print(++i); //10

    list.push_list_before_index(list2, 0);
    
    list.print(++i); //11
 
    list.push_list_before_index(list2, 1);
    
    list.print(++i); //12

    list.clear();
    list.print(++i); //13
    if (list.is_clear())
        std::cout << "List is clear" << std::endl;
    else
        std::cout << "List is not clear" << std::endl;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.print(++i); //14

    list2.clear();
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    list2.print(++i); //15

    if (list.in(list2))
        std::cout << "List2 is in List" << std::endl;
    else
        std::cout << "List2 is not in List" << std::endl;

    std::cout << "First inclusion: " << list.find_first_inclusion(list2) << std::endl;
    std::cout << "Last inclusion: " << list.find_last_inclusion(list2) << std::endl;

    list2.push_back(3);

    list2.print(++i); //16

    if (list.in(list2))
        std::cout << "List2 is in List" << std::endl;
    else
        std::cout << "List2 is not in List" << std::endl;

    list.print(++i); //17 
    
    std::cout << "First inclusion: " << list.find_first_inclusion(list2) << std::endl;
    std::cout << "Last inclusion: " << list.find_last_inclusion(list2) << std::endl;
    std::cout << "Get: " << list.get(0) << std::endl;
    list.set(10, 0);
    std::cout << "Get: " << list.get(0) << std::endl;

    std::cout << "Size: " << list.size() << std::endl;

    list.reverse();
    list.print(++i); //18
    list2.print(++i); //19

    list.permutation(list2, 0, 1);
    list.print(++i); //20
    list2.print(++i); //21

    return 0;
}