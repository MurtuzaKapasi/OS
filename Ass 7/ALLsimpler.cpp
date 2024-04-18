#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

using namespace std;

int FIFO(int pages[], int n, int capacity)
{
    queue<int> pageQueue;
    unordered_map<int, int> pageMap;

    int faults = 0;
    for (int i = 0; i < n; i++)
    {
        if (pageMap.find(pages[i]) == pageMap.end())
        {
            faults++;
            if (pageQueue.size() == capacity)
            {
                int front = pageQueue.front();
                pageQueue.pop();
                pageMap.erase(front);
            }

            pageQueue.push(pages[i]);
            pageMap[pages[i]] = 1;
        }
    }
    return faults;
}

int LRU(int pages[], int n, int capacity)
{
    list<int> lru;
    unordered_map<int, list<int>::iterator> pageMap;

    int faults = 0;
    for (int i = 0; i < n; i++)
    {
        if (pageMap.find(pages[i]) == pageMap.end())
        {
            faults++;
            if (lru.size() == capacity)
            {
                int leastUsed = lru.back();
                lru.pop_back();
                pageMap.erase(leastUsed);
            }
            lru.push_front(pages[i]);
            pageMap[pages[i]] = lru.begin();
        }
        else
        {
            lru.erase(pageMap[pages[i]]);
            lru.push_front(pages[i]);
            pageMap[pages[i]] = lru.begin();
        }
    }
    return faults;
}

int Optimal(int pages[], int n, int capacity)
{
    unordered_map<int, int> pageMap;
    vector<int> pageVector(capacity, -1);
    int faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (pageMap.find(pages[i]) == pageMap.end())
        {
            faults++;
            if (pageMap.size() == capacity)
            { // if capacity is full
                int index = 0, farthest = -1;
                for (int j = 0; j < capacity; j++)
                {
                    int farthestIndex = -1;
                    for (int k = i + 1; k < n; k++)
                    {
                        if (pages[k] == pageVector[j])
                        {
                            farthestIndex = k;
                            break;
                        }
                    }
                    if (farthestIndex == -1) // page is absent
                    {
                        index = j;
                        break;
                    }
                    else if (farthestIndex > farthest)
                    {
                        farthest = farthestIndex;
                        index = j;
                    }
                }
                pageMap.erase(pageVector[index]);
                pageVector[index] = pages[i];
            }
            else
            { // if capacity is not full
                for (int j = 0; j < capacity; j++)
                {
                    if (pageVector[j] == -1)
                    {
                        pageVector[j] = pages[i];
                        break;
                    }
                }
            }
            pageMap[pages[i]] = i;
        }
    }
    return faults;
}

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;

    cout << "FIFO Page Faults: " << FIFO(pages, n, capacity) << endl;
    cout << "LFU Page Faults: " << LRU(pages, n, capacity) << endl;
    cout << "Optimal Page Faults: " << Optimal(pages, n, capacity) << endl;

    return 0;
}