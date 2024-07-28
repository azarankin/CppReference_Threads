//01_Unique_Lock

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// Shared resource
int sharedCounter = 0;

// Mutex for synchronization
std::mutex mtx1;

// Function to increment the shared counter
void incrementCounter(int id)
{
	for (int i = 0; i < 10; ++i)
	{
		std::unique_lock<std::mutex> lock(mtx1);
		++sharedCounter;
	}
}

void incrementCounter_without_unique_lock(int id)
{
	for (int i = 0; i < 10; ++i)
	{
		//std::unique_lock<std::mutex> lock(mtx1);
		++sharedCounter;
	}
}



int main()
{
	{
		sharedCounter = 0;
		const int numThreads = 5000;
		std::vector<std::thread> threads;

		// Create and start multiple threads
		for (int i = 0; i < numThreads; ++i)
		{
			threads.emplace_back(incrementCounter, i);
		}

		// Join all threads to the main thread
		for (auto& thread : threads)
		{
			thread.join();
		}

		std::cout << "Final counter value: " << sharedCounter << std::endl;	//always 5000
	}

	{
		sharedCounter = 0;
		const int numThreads = 5000;
		std::vector<std::thread> threads;

		// Create and start multiple threads
		for (int i = 0; i < numThreads; ++i)
		{
			threads.emplace_back(incrementCounter_without_unique_lock, i);
		}

		// Join all threads to the main thread
		for (auto& thread : threads)
		{
			thread.join();
		}

		std::cout << "Final counter value without unique_lock: " << sharedCounter << std::endl; //not 5000
	}



	return 0;
}
