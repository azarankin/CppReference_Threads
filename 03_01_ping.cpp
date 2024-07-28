#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <string>

int main()
{
    std::cout << "Ping Server" << std::endl;
    Sleep(1000);
    HANDLE pingSemaphore = CreateSemaphore(NULL, 0, 1, L"ping");
    HANDLE pongSemaphore = CreateSemaphore(NULL, 1, 1, L"pong");

    while (true) {

        WaitForSingleObject(pingSemaphore, INFINITE);

        std::cout << "\rPing" << std::flush;
        Sleep(1000);
        std::cout << "\r    " << std::flush;
        Sleep(1000);
        ReleaseSemaphore(pongSemaphore, 1, NULL);
    }

    CloseHandle(pingSemaphore);
    CloseHandle(pongSemaphore);
    return 0;
}
