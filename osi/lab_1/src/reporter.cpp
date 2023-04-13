#include <iostream>
#include <fstream>
#include <string>
#include "../include/employee.h"

void writeData(std::ifstream &binFile, std::ofstream &repFile, double salaryPerHour)
{
    employee rec;
    repFile << "Employee \tName\tHours\tSalary\n";
    while (binFile.read((char*)(&rec), sizeof(rec)))
    {
        double salary = rec.hours * salaryPerHour;
        repFile << rec.num 
            << "\t\t" << rec.name 
            << "\t" << rec.hours 
            << "\t" << salary << "$\n";
    }
}

template < typename T >
void checkFile(T &file, std::string attributeName)
{
    if (!file)
    {
        std::cerr << "Error: opening " + attributeName+ " file";
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Error: must be 4 args" << std::endl;
        return 1;
    }

    std::string binFileName = argv[1];
    std::ifstream binFile(binFileName, std::ios::binary);
    checkFile(binFile, "bin");

    std::string repFileName = argv[2];
    std::ofstream repFile(repFileName);
    checkFile(repFile, "report");

    double salaryPerHour = std::stod(argv[3]);
    writeData(binFile, repFile, salaryPerHour);
    binFile.close();
    repFile.close();
    return 0;
}
