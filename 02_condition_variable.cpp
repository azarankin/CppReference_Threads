//02_Condition_Variable

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx2;
std::condition_variable cv2;
bool pingTurn = true;

void ping()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx2);
        cv2.wait(lock, [] { return pingTurn; }); // Wait for ping's turn

        std::cout << "Ping" << std::endl;
        pingTurn = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));


        cv2.notify_one(); // Notify pong
    }
}

void pong()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx2);
        cv2.wait(lock, [] { return !pingTurn; }); // Wait for pong's turn

        std::cout << "Pong" << std::endl;
        pingTurn = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        cv2.notify_one(); // Notify ping
    }
}

int main()
{
    std::thread pingThread(ping);
    std::thread pongThread(pong);

    pingThread.join();
    pongThread.join();

    return 0;
}
