#include<bits/stdc++.h>
using namespace std;

//Function to implement FIFO page replacement algorithm
int FIFO(const vector<int> &pages, int capacity)
{
    queue<int> pageQueue;       // Queue to store pages in memory
    unordered_set<int> pageSet; // Set to keep track of pages in memory
    int pageFaults = 0;         // Counter for page faults

    for (int page : pages)
    {
        if (pageSet.find(page) == pageSet.end())
        {
            if (pageQueue.size() == capacity)
            {
                int oldest = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(oldest);
            }
            pageQueue.push(page);
            pageSet.insert(page);
            ++pageFaults;
        }
    }
    return pageFaults;
}

int LRU(const vector<int> &pages, int capacity)
{
    int pageFaults = 0;                              // Counter for page faults
    list<int> lru;                                   // List to maintain the least recently used order
    unordered_map<int, list<int>::iterator> pageMap; // Map to store page positions in list

    for (int page : pages)
    {
        if (pageMap.find(page) == pageMap.end())
        {
            if (lru.size() == capacity)
            {
                int leastUsed = lru.back();
                lru.pop_back();
                pageMap.erase(leastUsed);
            }
            lru.push_front(page);
            pageMap[page] = lru.begin();
            ++pageFaults;
        }
        else
        {
            lru.erase(pageMap[page]);
            lru.push_front(page);
            pageMap[page] = lru.begin();
        }
    }
    return pageFaults;
}

// Optimal Page Replacement Algorithm
int Optimal(vector<int> pages,  int n, int capacity) {
    unordered_map<int, int> pageMap;
    vector<int> pageVector(capacity, -1);

    int pageFaults = 0;
    for (int i = 0; i < n; i++) {
        if (pageMap.find(pages[i]) == pageMap.end()) {
            pageFaults++;
            if (pageVector.size() == capacity) {
                int index = 0, farthest = -1;
                for (int j = 0; j < capacity; j++) {
                    if (pageMap.find(pageVector[j]) == pageMap.end()) {
                        index = j;
                        break;
                    } else if (pageMap[pageVector[j]] > farthest) {
                        farthest = pageMap[pageVector[j]];
                        index = j;
                    }
                }
                pageMap.erase(pageVector[index]);
                pageVector[index] = pages[i];
            } else {
                for (int j = 0; j < capacity; j++) {
                    if (pageVector[j] == -1) {
                        pageVector[j] = pages[i];
                        break;
                    }
                }
            }
            pageMap[pages[i]] = i;
        }
    }

    return pageFaults;
}

int main()
{
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2,1,2,0,1,7,0,1};
    int n = pages.size();

    int capacity = 4;
    int pageFaults;
    
    // cout << "Enter the memory capacity: ";
    // cin >> capacity;

    // int choice;
    // cout << "Choose a page replacement algorithm:\n"
    //      << "1. FIFO\n"
    //      << "2. LRU\n"
    //      << "Enter your choice: ";
    // cin >> choice;

    // switch (choice) {
    //     case 1:
    //         pageFaults = FIFO(pages, capacity);
    //         cout << "Total page faults using FIFO: " << pageFaults << endl;
    //         break;
    //     case 2:
    //         pageFaults = LRU(pages, capacity);
    //         cout << "Total page faults using LRU: " << pageFaults << endl;
    //         break;
    //     default:
    //         cout << "Invalid choice" << endl;
    // }

    cout << "Total page faults in FIFO " << FIFO(pages, capacity) << endl;
    cout << "Total page faults in LRU " << LRU(pages, capacity) << endl;
    cout << "Total page faults in Optimal " << Optimal(pages,n, capacity) << endl;

    return 0;
}
