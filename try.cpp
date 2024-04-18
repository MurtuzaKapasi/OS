#include <unordered_map>
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

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
                    if (farthestIndex == -1)
                    {
                        index = j;
                        break;
                    }
                    else
                    {
                        if (farthestIndex > farthest)
                        {
                            farthest = farthestIndex;
                            index = j;
                        }
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
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;
    int faults = Optimal(pages, n, capacity);
    
    cout<<"Total page faults using Optimal: "<<faults<<endl;
    return 0;
}
