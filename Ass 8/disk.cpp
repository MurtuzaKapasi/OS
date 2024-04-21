#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define MAX_REQUESTS 1000
#define MAX_TRACKS 10000

// Function to sort array in ascending order
// void bubbleSort(vector<int>& arr)
// {
//     int n = arr.size();
//     for (int i = 0; i < n - 1; i++)
//     {
//         for (int j = 0; j < n - i - 1; j++)
//         {
//             if (arr[j] > arr[j + 1])
//             {
//                 int temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//             }
//         }
//     }
// }

// // Function to find index of nearest track
// int findNearest(const vector<int>& tracks, int head)
// {
//     int minDist = abs(tracks[0] - head);
//     int index = 0;
//     for (int i = 1; i < tracks.size(); i++)
//     {
//         int dist = abs(tracks[i] - head);
//         if (dist < minDist)
//         {
//             minDist = dist;
//             index = i;
//         }
//     }
//     return index;
// }

// Function to implement FIFO scheduling algorithm
void fifo(const vector<int>& requests, int head)
{
    int totalSeek = 0;
    for (int i = 0; i < requests.size(); i++)
    {
        totalSeek += abs(head - requests[i]);
        head = requests[i];
    }
    cout << "FIFO: Total Seek Time = " << totalSeek << endl;
}

// Function to implement SSTF scheduling algorithm
void sstf(const vector<int>& requests, int head)
{
    int totalSeek = 0;
    vector<bool> visited(requests.size(), false);
    for (int i = 0; i < requests.size(); i++)
    {
        int minDist = MAX_TRACKS;
        int index = -1;
        for (int j = 0; j < requests.size(); j++)
        {
            if (!visited[j])
            {
                int dist = abs(head - requests[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    index = j;
                }
            }
        }
        totalSeek += minDist;
        head = requests[index];
        visited[index] = true;
    }
    cout << "SSTF: Total Seek Time = " << totalSeek << endl;
}

// Function to implement SCAN scheduling algorithm
void scan(const vector<int>& requests, int head, int maxTrack)
{
    int totalSeek = 0;
    vector<int> sortedRequests = requests;
    sort(sortedRequests.begin(), sortedRequests.end());
    auto it = lower_bound(sortedRequests.begin(), sortedRequests.end(), head);
    if (it != sortedRequests.end())
    {
        totalSeek += abs(head - *it);
        head = *it;
        for (auto itr = it; itr != sortedRequests.end(); ++itr)
        {
            totalSeek += abs(head - *itr);
            head = *itr;
        }
        totalSeek += abs(maxTrack - head);
        head = maxTrack;
    }
    cout << "SCAN: Total Seek Time = " << totalSeek << endl;
}

// Function to implement C-SCAN scheduling algorithm
void cscan(const vector<int>& requests, int head, int maxTrack)
{
    int totalSeek = 0;
    vector<int> sortedRequests = requests;
    sort(sortedRequests.begin(), sortedRequests.end());
    auto it = lower_bound(sortedRequests.begin(), sortedRequests.end(), head);
    if (it != sortedRequests.end())
    {
        totalSeek += abs(head - *it);
        head = *it;
        for (auto itr = it; itr != sortedRequests.end(); ++itr)
        {
            totalSeek += abs(head - *itr);
            head = *itr;
        }
        totalSeek += abs(0 - head);
        head = 0;
        totalSeek += abs(maxTrack - head);
        head = maxTrack;
    }
    cout << "C-SCAN: Total Seek Time = " << totalSeek << endl;
}

int main()
{
    vector<int> requests;
    int n, head, maxTrack;
    int choice;
    char repeat;
    
    do {
        // Input number of requests
        cout << "Enter the number of disk requests: ";
        cin >> n;

        // Input disk requests
        cout << "Enter the disk requests: ";
        for (int i = 0; i < n; i++)
        {
            int request;
            cin >> request;
            requests.push_back(request);
        }

        // Input current head position
        cout << "Enter the current head position: ";
        cin >> head;

        // Input maximum track number
        cout << "Enter the maximum track number: ";
        cin >> maxTrack;

        // Menu
        cout << "Select Scheduling Algorithm:" << endl;
        cout << "1. FIFO" << endl;
        cout << "2. SSTF" << endl;
        cout << "3. SCAN" << endl;
        cout << "4. C-SCAN" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform selected scheduling algorithm
        switch (choice)
        {
            case 1:
                fifo(requests, head);
                break;
            case 2:
                sstf(requests, head);
                break;
            case 3:
                scan(requests, head, maxTrack);
                break;
            case 4:
                cscan(requests, head, maxTrack);
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        // Clear requests vector for next iteration
        requests.clear();

        // Ask user if they want to repeat
        cout << "Do you want to perform another scheduling (y/n)? ";
        cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');

    return 0;
}
