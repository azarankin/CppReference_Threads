#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <string>

int main()
{
    std::cout << "Pong Server" << std::endl;
    HANDLE pingSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"ping");
    HANDLE pongSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"pong");

    while (true) {
        WaitForSingleObject(pongSemaphore, INFINITE);

        std::cout << "\rPong" << std::flush;
        Sleep(1000);
        std::cout << "\r    " << std::flush;
        Sleep(1000);
        ReleaseSemaphore(pingSemaphore, 1, NULL);
    }

    CloseHandle(pingSemaphore);
    CloseHandle(pongSemaphore);
    return 0;
}
