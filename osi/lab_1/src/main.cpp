#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <string>
#include "../include/employee.h"

template < typename T >
void enterData(std::string &FileName, T &data, std::string fileType, std::string dataType)
{
    std::cout << "Enter " + fileType + " file name: ";
    getline(std::cin, FileName);
    FileName = "files/" + FileName;
    std::cout << "Enter " + dataType+ ": ";
    std::cin >> data;

    if (fileType == "bin" && FileName.substr(FileName.size() - 4, FileName.size() - 1) != ".bin")
        FileName += ".bin";
    else if (fileType == "rep" && FileName.substr(FileName.size() - 4, FileName.size() - 1) != ".txt")
        FileName += ".txt";
}

void createProc(std::string command)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    TCHAR commandLine[MAX_PATH];
    _tcscpy_s(commandLine, MAX_PATH, command.c_str());
    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "Error: Can't create process";
        exit(1);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
}

void outEmployees(std::string binFileName)
{
    std::ifstream readFile(binFileName, std::ios::binary);
    if (!readFile) {
        std::cerr << "Error: Could not open bin file";
        exit(1);
    }

    employee person;
    std::cout << "Employee list:\n";
    while (readFile.read(reinterpret_cast<char*>(&person), sizeof(person))) {
        std::cout << "\tID: " << person.num << '\n';
        std::cout << "\tName: " << person.name << '\n';
        std::cout << "\tHours: " << person.hours << '\n';
        std::cout << '\n';
    }
    readFile.close();
}

void outReport(std::string binFileName, std::string reportFileName)
{
    std::ifstream readFile;
    readFile.open(reportFileName);
    if (!readFile) {
        std::cerr << "Error: Could not open report file" << '\n';
        exit(1);
    }

    std::string record;
    std::cout << "Report data:\n";
    while (std::getline(readFile, record))
        std::cout << '\t' << record << '\n';
    readFile.close();
}

int main(int argc, char* argv[]) 
{
    std::string binFileName;
    int recordsCount;
    enterData(binFileName, recordsCount, "bin", "employees count");

    std::string command = "Creator.exe " + binFileName + " " + std::to_string(recordsCount);
    createProc(command);
    outEmployees(binFileName);
    
    std::string reportFileName;
    double salary;
    std::cin.ignore();
    enterData(reportFileName, salary, "rep", "salary for hour");

    command = "Reporter.exe " + binFileName + " " + reportFileName + " " + std::to_string(salary);
    createProc(command);
    outReport(binFileName, reportFileName);
    
    return 0;
}
