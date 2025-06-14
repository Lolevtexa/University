#include "../lib/Task/Task.hpp"


int main()
{
    writeToFile
    (
        "files/output.txt", 
        processing
        (
            writeToFile
            (
                "files/output.txt",
                readFromFile
                (
                    "files/input.txt"
                ),
                std::ios::out
            )
        ),
        std::ios::app
    );

    return 0;
}
