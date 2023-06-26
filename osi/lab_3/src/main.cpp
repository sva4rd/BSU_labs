#include <windows.h>
#include <iostream>

struct ThreadParameters 
{
    HANDLE handle;
    int num;
    bool stopped = false;
    int markedCount = 0;
};

HANDLE* mainHandles;
HANDLE* threadHandles;
CRITICAL_SECTION cs;
int* arr;
int size;

DWORD WINAPI Marker(LPVOID thread) 
{
    auto currentThread = (ThreadParameters*)thread;
    EnterCriticalSection(&cs);
    srand(currentThread->num);

    auto* marked = new bool[size];
    for (int i = 0; i < size; i++)
        marked[i] = false;
    LeaveCriticalSection(&cs);

    while (true) 
    {
        int num = rand();
        EnterCriticalSection(&cs);
        LeaveCriticalSection(&cs);
        num %= size;
        EnterCriticalSection(&cs);
        if (arr[num] == 0)
        {
            Sleep(5);
            arr[num] = currentThread->num;
            marked[num] = true;
            ++currentThread->markedCount;
            LeaveCriticalSection(&cs);
            Sleep(5);
        }
        else if (arr[num] != 0)
        {
            std::cout << "\nMarker " << currentThread->num
                << "\n\tCan't modify " << num << " element"
                << "\n\tMarked elements: " << currentThread->markedCount << '\n';
            LeaveCriticalSection(&cs);

            SetEvent(threadHandles[currentThread->num - 1]);
            WaitForSingleObject(mainHandles[currentThread->num - 1], INFINITE);
            ResetEvent(threadHandles[currentThread->num - 1]);
            ResetEvent(mainHandles[currentThread->num - 1]);
            WaitForSingleObject(mainHandles[currentThread->num - 1], INFINITE);

            if (currentThread->stopped) 
            {
                EnterCriticalSection(&cs);
                for (int i = 0; i < size; i++)
                    if (marked[i])
                        arr[i] = 0;
                currentThread->markedCount = 0;
                LeaveCriticalSection(&cs);
                break;

            }
        }
    }
    delete[] marked;

    SetEvent(threadHandles[currentThread->num - 1]);

    EnterCriticalSection(&cs);
    LeaveCriticalSection(&cs);
    return 0;
}

int main() 
{
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    arr = new int[size];
    std::fill(arr, arr + size, 0);

    std::cout << "\nEnter the number of threads: ";
    int threadsNum;
    std::cin >> threadsNum;

    ThreadParameters** threads = new ThreadParameters*[threadsNum];
    DWORD dword;
    InitializeCriticalSection(&cs);


    mainHandles = new HANDLE[threadsNum];
    threadHandles = new HANDLE[threadsNum];
    for (int i = 0; i < threadsNum; i++) 
    {
        threads[i] = new ThreadParameters;
        mainHandles[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        threadHandles[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        (*threads[i]).num = i + 1;
        (*threads[i]).handle = CreateThread(nullptr, 0, Marker, (LPVOID)threads[i], 0, &dword);
    }

    int n;
    for (int i = 0; i < threadsNum; i++) 
    {
        WaitForMultipleObjects(threadsNum, threadHandles, TRUE, INFINITE);
        for (int j = 0; j < threadsNum; j++)
            SetEvent(mainHandles[j]);
        EnterCriticalSection(&cs);

        std::cout << "\nArray: ";
        for (int q = 0; q < size; q++)
            std::cout << arr[q] << " ";
        std::cout << '\n';

        do
        {
            std::cout << "\nEnter the num of thread to stop: ";
            std::cin >> n;
            if (n <= 0 || n > threadsNum)
                std::cout << "Error: Wrong thread number\n";
            else if (threads[n - 1]->stopped)
                std::cout << "This thread is already finished\n";

        } while (n <= 0 || n > threadsNum || threads[n - 1]->stopped);

        (*threads[n - 1]).stopped = true;
        LeaveCriticalSection(&cs);

        SetEvent(mainHandles[n - 1]);
        WaitForSingleObject(threadHandles[n - 1], INFINITE);

        for (int j = 0; j < threadsNum; j++)
        {
            SetEvent(mainHandles[j]);
            ResetEvent(mainHandles[j]);
        }
    }

    for (int i = 0; i < threadsNum; i++)
    {
        CloseHandle(threads[i]->handle);
        CloseHandle(threadHandles[i]);
        CloseHandle(mainHandles[i]);
    }

    delete[] threads;
    delete[] threadHandles;
    delete[] mainHandles;
    DeleteCriticalSection(&cs);
    delete[] arr;
    return 0;
}