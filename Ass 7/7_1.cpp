#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;
// Function prototypes
void FIFO(const vector<int> &pages, int frameSize);
void LRU(const vector<int> &pages, int frameSize);
void Optimal(const vector<int> &pages, int frameSize);
int main()
{
    bool exit = false;
    while (!exit)
    {
        vector<int> pages;
        int frameSize, pageSize, page;
        cout << "Enter the number of pages: ";
        cin >> pageSize;
        cout << "Enter the page reference sequence:" << endl;
        for (int i = 0; i < pageSize; ++i)
        {
            cin >> page;
            pages.push_back(page);
        }
        cout << "Enter frame size: ";
        cin >> frameSize;
        int choice;
        cout << "Choose Page Replacement Algorithm:" << endl;
        cout << "1. FIFO" << endl;
        cout << "2. LRU" << endl;
        cout << "3. Optimal" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            FIFO(pages, frameSize);
            break;
        case 2:
            LRU(pages, frameSize);
            break;
        case 3:
            Optimal(pages, frameSize);
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
        char choiceExit;
        cout << "Do you want to exit? (y/n): ";
        cin >> choiceExit;
        if (choiceExit == 'y' || choiceExit == 'Y')
        {
            exit = true;
        }
    }
    return 0;
}
void FIFO(const vector<int> &pages, int frameSize)
{
    queue<int> fifoQueue;
    unordered_map<int, bool> pagePresent;
    int pageFaults = 0;
    cout << "Step\tFrames\t\tPage Faults" << endl;
    for (int page : pages)
    {
        cout << "--------------------------------------" << endl;
        cout << page << "\t";
        if (fifoQueue.size() < frameSize)
        {
            if (!pagePresent[page])
            {
                fifoQueue.push(page);
                pagePresent[page] = true;
                pageFaults++;
            }
        }
        else
        {
            if (!pagePresent[page])
            {
                int victim = fifoQueue.front();
                fifoQueue.pop();
                pagePresent[victim] = false;
                fifoQueue.push(page);
                pagePresent[page] = true;
                pageFaults++;
            }
        }
        for (int i = 0; i < fifoQueue.size(); ++i)
        {
            cout << fifoQueue.front() << " ";
            fifoQueue.push(fifoQueue.front());
            fifoQueue.pop();
        }
        cout << "\t\t" << pageFaults << endl;
    }
    cout << "FIFO Page Faults: " << pageFaults << endl;
}
void LRU(const vector<int> &pages, int frameSize)
{
    unordered_map<int, int> pageLastUse;
    vector<int> frames;
    int pageFaults = 0;
    cout << "Step\tFrames\t\tPage Faults" << endl;
    for (int i = 0; i < pages.size(); ++i)
    {
        cout << "--------------------------------------" << endl;
        int page = pages[i];
        cout << page << "\t";
        auto it = find(frames.begin(), frames.end(), page);
        if (it != frames.end())
        {
            pageLastUse[page] = i;
        }
        else
        {
            if (frames.size() < frameSize)
            {
                frames.push_back(page);
                pageLastUse[page] = i;
                pageFaults++;
            }
            else
            {
                int victim = frames[0];
                for (int j = 1; j < frameSize; ++j)
                {
                    if (pageLastUse[frames[j]] < pageLastUse[victim])
                    {
                        victim = frames[j];
                    }
                }
                it = find(frames.begin(), frames.end(), victim);
                *it = page;
                pageLastUse[page] = i;
                pageFaults++;
            }
        }
        for (int frame : frames)
        {
            cout << frame << " ";
        }
        cout << "\t\t" << pageFaults << endl;
    }
    cout << "LRU Page Faults: " << pageFaults << endl;
}
void Optimal(const vector<int> &pages, int frameSize)
{
    vector<int> frames(frameSize, -1); // Initialize frames with -1 indicating empty
    int pageFaults = 0;
    cout << "Step\tFrames\t\tPage Faults" << endl;
    for (int i = 0; i < pages.size(); ++i)
    {
        cout << "--------------------------------------" << endl;
        bool pageFound = false;
        int page = pages[i];
        cout << page << "\t";
        // Check if the page is already in frames
        for (int j = 0; j < frameSize; ++j)
        {
            if (frames[j] == page)
            {
                pageFound = true;
                break;
            }
        }
        // If page not found in frames, replace the page with the farthest next use
        if (!pageFound)
        {
            int farthestIndex = i;
            int pageToReplace = -1;
            for (int j = 0; j < frameSize; ++j)
            {
                int k;
                for (k = i + 1; k < pages.size(); ++k)
                {
                    if (frames[j] == pages[k])
                    {
                        if (k > farthestIndex)
                        {
                            farthestIndex = k;
                            pageToReplace = j;
                        }
                        break;
                    }
                }
                // If the page is not found in the future, replace it
                if (k == pages.size())
                {
                    pageToReplace = j;
                    break;
                }
            }
            frames[pageToReplace] = pages[i];
            pageFaults++;
        }
        for (int frame : frames)
        {
            cout << frame << " ";
        }
        cout << "\t\t" << pageFaults << endl;
    }
    cout << "Optimal Page Faults: " << pageFaults << endl;
}
