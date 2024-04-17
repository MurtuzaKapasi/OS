#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex x, y;
std::vector<std::thread> writerthreads, readerthreads;
int readercount = 0;

void reader()
{
    x.lock();
    readercount++;
    if (readercount == 1)
        y.lock();
    x.unlock();

    std::cout << readercount << " reader is inside" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Simulate reading

    x.lock();
    readercount--;
    if (readercount == 0)
        y.unlock();
    x.unlock();

    std::cout << readercount + 1 << " Reader is leaving" << std::endl;
}

void writer()
{
    std::cout << "Writer is trying to enter" << std::endl;
    y.lock();
    std::cout << "Writer has entered" << std::endl;
    y.unlock();
    std::cout << "Writer is leaving" << std::endl;
}

int main()
{
    int n2, i;
    std::cout << "Enter the number of readers:";
    std::cin >> n2;
    std::cout << std::endl;
    
    writerthreads.reserve(n2);
    readerthreads.reserve(n2);

    for (i = 0; i < n2; i++)
    {
        readerthreads.emplace_back(reader);
        writerthreads.emplace_back(writer);
    }

    for (i = 0; i < n2; i++)
    {
        readerthreads[i].join();
        writerthreads[i].join();
    }

    return 0;
}
