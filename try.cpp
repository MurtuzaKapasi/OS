#include <bits/stdc++.h>
using namespace std;

int FIFO(int pages[], int n, int capacity){
    unordered_map<int, int> pageMap;
    queue<int> pageQueue;

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


int Optimal(int pages[], int n, int capacity){
    vector<int> pageVector(capacity, -1);
    map<int , int> pageMap;
     int faults = 0; 
    for(int i=0 ; i<n ; i++){
        if(pageMap.find(pages[i]) == pageMap.end()){
            faults++;
            if(pageMap.size() == capacity){
                int farthestIndex = -1 , index = 0;
                for(int j=0 ; j< capacity ; j++){
                    int fartherst = -1;
                    for(int k= i+1 ; k< n ; k++){
                        if(pages[k] == pageVector[j]){
                            fartherst = k;
                            break;
                        }
                    }
                    if(fartherst == -1){
                        index = j;
                        break;
                    }
                    else if(fartherst > farthestIndex){
                        farthestIndex = fartherst;
                        index = j;
                    }
                }

                pageMap.erase(pageVector[index]);
                pageVector[index] = pages[i];

            }
            else{
                for(int j=0 ; j<capacity ; j++){
                    if(pageVector[j] == -1){
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
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2,1,2,0,1,7,0,1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;

    cout << "Total page faults using FIFO: " << FIFO(pages, n, capacity) << endl;
    cout << "Total page faults using LRU: " << LRU(pages, n, capacity) << endl;
    cout<<"Total page faults using Optimal: "<<Optimal(pages, n, capacity)<<endl;
    return 0;
}
