#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std;


mutex x, db;
vector<thread> writerthreads, readerthreads;
int readercount = 0;

void reader()
{
    x.lock();
    readercount++;
    if (readercount == 1)
        db.lock();
    x.unlock();

    cout << readercount << " reader is inside" << endl;
    this_thread::sleep_for(chrono::milliseconds(300)); // Simulate reading

    x.lock();
    readercount--;
    if (readercount == 0)
        db.unlock();
    x.unlock();

    cout << readercount + 1 << " Reader is leaving" << endl;
}

void writer()
{
    cout << "Writer is trying to enter" << endl;
    db.lock();
    cout << "Writer has entered" << endl;
    db.unlock();
    cout << "Writer is leaving" << endl;
}

int main()
{
    int n, i;
    cout << "Enter the number of readers:";
    cin >> n;
    
    writerthreads.reserve(n);
    readerthreads.reserve(n);

    for (i = 0; i < n; i++)
    {
        readerthreads.emplace_back(reader);
        writerthreads.emplace_back(writer);
    }

    for (i = 0; i < n; i++)
    {
        readerthreads[i].join();
        writerthreads[i].join();
    }

    return 0;
}
