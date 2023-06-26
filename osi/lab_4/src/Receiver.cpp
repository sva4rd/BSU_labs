#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <charconv>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Enter the name of the source file: ";
    std::string fileName;
    std::cin >> fileName;
    fileName = "files/" + fileName;
    std::cout << "Enter the number of Sender processes: ";
    int sendersCount;
    while (true)
    {
        std::cin >> sendersCount;
        if (sendersCount <= 0)
        {
            std::cout << "\nError: Wrong number of processes\nTry again: ";
            continue;
        }
        break;
    }

    STARTUPINFOA* sendersSI = new STARTUPINFOA[sendersCount];
    PROCESS_INFORMATION* sendersPI = new PROCESS_INFORMATION[sendersCount];
    HANDLE* busyEvents = new HANDLE[sendersCount];
    HANDLE* senders = new HANDLE[sendersCount];
    std::fstream fin(fileName, std::ios_base::trunc | std::ios_base::out | std::ios_base::binary | std::ios_base::in);

    SECURITY_ATTRIBUTES securityAttributes = {sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE};
    HANDLE startupEvent = CreateEventA(&securityAttributes, TRUE, FALSE, "SenderStartupEvent");
    HANDLE mutex = CreateMutexA(&securityAttributes, FALSE, "SenderWriteMutex");

    for (int i = 0; i < sendersCount; i++) {
        ZeroMemory(&sendersSI[i], sizeof(STARTUPINFO));
        sendersSI[i].cb = sizeof(STARTUPINFO);
        ZeroMemory(&sendersPI[i], sizeof(PROCESS_INFORMATION));
        busyEvents[i] = CreateEventA(&securityAttributes, FALSE, FALSE, ("busyEvent" + std::to_string(i)).c_str());

        std::string arguments = fileName + " busyEvent" + std::to_string(i);
        const char* appName = "C:\\Users\\User\\Desktop\\BSU labs\\osi\\lab_4\\bin\\Sender.exe";
        if (!CreateProcessA(appName, (char*)arguments.c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &sendersSI[i], &sendersPI[i])) {
            std::cout << "Error: Unable to create \"Sender.exe\" process";
            ExitProcess(0);
        }
        senders[i] = sendersPI[i].hProcess;
    }

    WaitForMultipleObjects(sendersCount, busyEvents, TRUE, INFINITE);
    SetEvent(startupEvent);
    std::string response;
    while (WaitForMultipleObjects(sendersCount, senders, TRUE, 0) == WAIT_TIMEOUT) 
    {
        std::cout << "Enter 0 to try to read messages from the file: ";
        while (true)
        {
            std::cin >> response;
            if (response.compare("0") != 0)
                continue;
            break;
        }

        std::string message;
        fin.sync();
        if (!(std::getline(fin, message))) 
        {
            std::cout << "There are no new messages. Waiting.\n";
            fin.clear();
            ResetEvent(startupEvent); 
            
            do {
                if (WaitForMultipleObjects(sendersCount, busyEvents, FALSE, 5000) != WAIT_TIMEOUT)
                    break;
            } while (WaitForMultipleObjects(sendersCount, senders, TRUE, 0) == WAIT_TIMEOUT);
            SetEvent(startupEvent);
        }
        else 
            std::cout << message << '\n'; 

        while (std::getline(fin, message))
            std::cout << message << '\n';
        fin.clear();
    }

    for (int i = 0; i < sendersCount; i++) 
    {
        CloseHandle(sendersPI[i].hThread);
        CloseHandle(sendersPI[i].hProcess);
        CloseHandle(busyEvents[i]);
    }
    CloseHandle(startupEvent);
    CloseHandle(mutex);
    fin.close();
    return 0;
}
