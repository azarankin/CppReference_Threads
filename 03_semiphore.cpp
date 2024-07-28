#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <string>
void func_main1()
{
    std::cout << "Running Function 1" << std::endl;
    // Add your function logic here
    std::cout << "Ping Server" << std::endl;
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
}

void func_main2()
{
    std::cout << "Running Function 2" << std::endl;
    // Add your function logic here
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
}

void launchTerminalWithFunction(const std::string& executablePath, const std::string& funcName)
{
    std::string command = "start cmd /k \"" + executablePath + " " + funcName + "\"";
    int result = system(command.c_str());
    if (result != 0)
    {
        std::cerr << "Failed to launch terminal for function " << funcName << ", error code: " << result << std::endl;
    }
}

void runFunctionsInSeparateTerminals(const std::string& executablePath)
{
    std::thread t1([&]() { launchTerminalWithFunction(executablePath, "func_main1"); });
    std::thread t2([&]() { launchTerminalWithFunction(executablePath, "func_main2"); });

    t1.join();
    t2.join();
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::string executablePath = argv[0];
        runFunctionsInSeparateTerminals(executablePath);
    }
    else if (argc == 2)
    {
        std::string funcName = argv[1];

        if (funcName == "func_main1")
        {
            func_main1();
        }
        else if (funcName == "func_main2")
        {
            func_main2();
        }
        else
        {
            std::cerr << "Unknown function: " << funcName << std::endl;
            return 1;
        }
        std::cout << "Press any key to continue . . ." << std::endl;
        std::cin.get();  // Keep the terminal open
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " [func_main1|func_main2]" << std::endl;
        return 1;
    }

    return 0;
}
