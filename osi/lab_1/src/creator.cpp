#include <iostream>
#include <fstream>
#include "../include/employee.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: must be 3 args";
        return 1;
    }

    std::ofstream writeFile(argv[1], std::ios::binary);
    if (!writeFile) {
        std::cerr << "Error: Could not open bin file";
        return 1;
    }

    int num_records = std::atoi(argv[2]);
    employee record;

    for (int i = 0; i < num_records; i++) {
        std::cout << "Enter the details of employee " << i + 1 << ":" << '\n';
        std::cout << "ID: ";
        std::cin >> record.num;
        std::cout << "Name: ";
        std::cin >> record.name;
        std::cout << "Hours: ";
        std::cin >> record.hours;
        writeFile.write(reinterpret_cast<char*>(&record), sizeof(record));
    }
    
    writeFile.close();
    return 0;
}
