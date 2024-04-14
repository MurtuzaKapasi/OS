#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to implement FIFO page replacement algorithm
int FIFO(int pages[], int n, int capacity)
{
    queue<int> pageQueue;       // Queue to store pages in memory
    unordered_set<int> pageSet; // Set to keep track of pages in memory
    int pageFaults = 0;         // Counter for page faults

    for (int i = 0; i < n; ++i)
    {
        // If page is not in memory
        if (pageSet.find(pages[i]) == pageSet.end())
        {
            // If memory is full, remove oldest page
            if (pageQueue.size() == capacity)
            {
                int oldest = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(oldest);
            }
            // Add new page to memory
            pageQueue.push(pages[i]);
            pageSet.insert(pages[i]);
            ++pageFaults;
        }
    }
    return pageFaults;
}

int main()
{
    // Example usage

    int n; // Number of pages
    cout << "Enter the number of pages: ";
    cin >> n;

    int pages[n]; // Array to store page reference sequence
    cout << "Enter the page reference sequence: ";
    for (int i = 0; i < n; ++i)
        cin >> pages[i];

    int capacity; // Memory capacity
    cout << "Enter the memory capacity: ";
    cin >> capacity;

    int pageFaults = FIFO(pages, n, capacity);
    cout << "Total page faults using FIFO: " << pageFaults << endl;

    return 0;
}