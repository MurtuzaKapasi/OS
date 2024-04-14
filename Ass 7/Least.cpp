#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;
int LRU( vector<int>& pages, int capacity) {
    int pageFaults = 0; // Counter for page faults
    list<int> lru; // List to maintain the least recently used order
    unordered_map<int, list<int>::iterator> pageMap; // Map to store page positions in list

    for (int page : pages) {
        // If page is not in memory
        if (pageMap.find(page) == pageMap.end()) {
            // If memory is full, remove least recently used page
            if (lru.size() == capacity) {
                int leastUsed = lru.back();
                lru.pop_back();
                pageMap.erase(leastUsed);
            }
            // Add new page to memory
            lru.push_front(page);
            pageMap[page] = lru.begin();
            ++pageFaults;
        } else {
            // Move accessed page to front of LRU list
            lru.erase(pageMap[page]);
            lru.push_front(page);
            pageMap[page] = lru.begin();
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

    int pageFaults = LRU(pages, n);
    cout << "Total page faults using FIFO: " << pageFaults << endl;

    return 0;
}