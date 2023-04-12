#include <iostream>
#include <fstream>
#include "../include/employee.h"

template < typename T >
void enterData(std::string attributeName, T &attribute)
{
    std::cout << "\t" + attributeName + ": ";
    std::cin >> attribute;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: must be 3 args";
        return 1;
    }

    std::ofstream binFile(argv[1], std::ios::binary);
    if (!binFile) {
        std::cerr << "Error: Could not open bin file";
        return 1;
    }

    int amount = std::atoi(argv[2]);
    employee rec;
    std::cout << "Enter employees data:" << '\n';
    for (int i = 0; i < amount; i++) 
    {
        enterData("ID", rec.num);
        enterData("Name", rec.name);
        enterData("Hours", rec.hours);
        std::cout << '\n';
        binFile.write((char*)(&rec), sizeof(rec));
    }
    
    binFile.close();
    return 0;
}
