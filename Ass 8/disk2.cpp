#include <bits/stdc++.h>

using namespace std;

const int disk_size = 200;

class Node
{
public:
    int distance = 0;      // represent difference between head position and track number
    bool accessed = false; // true if track has been accessed
};

void FCFS(int arr[], int head, int n)
{
    int seek_count = 0;
    int distance, cur_track;

    for (int i = 0; i < n; i++)
    {
        cur_track = arr[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    cout << "Total number of seek operations = " << seek_count << endl;

    // Seek sequence would be the same as request array sequence
    cout << "Seek Sequence is" << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << endl;
}

void calculateDifference(int queue[], int head, Node diff[], int n)
{
    for (int i = 0; i < n; i++)
        diff[i].distance = abs(queue[i] - head);
}

int findMin(Node diff[], int n)
{
    int index = -1, minimum = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (!diff[i].accessed && minimum > diff[i].distance)
        {
            minimum = diff[i].distance;
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(int request[], int head, int n)
{
    if (n == 0)
        return;

    Node diff[n];
    int seek_count = 0;
    int seek_sequence[n + 1];

    for (int i = 0; i < n; i++)
    {
        seek_sequence[i] = head;
        calculateDifference(request, head, diff, n);
        int index = findMin(diff, n);
        diff[index].accessed = true;
        seek_count += diff[index].distance;
        head = request[index];
    }

    // for last accessed track
    seek_sequence[n] = head;

    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is" << endl;

    // print the sequence
    for (int i = 0; i <= n; i++)
        cout << seek_sequence[i] << endl;
}

void SCANDisk(int arr[], int head, string direction, int n)
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right, seek_sequence;

    // appending end values which has to be visited before reversing the direction
    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(disk_size - 1);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    // sorting left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // run the while loop two times. one by one scanning right and left of the head
    int run = 2;
    while (run-- > 0)
    {
        if (direction == "left")
        {
            for (int i = left.size() - 1; i >= 0; i--)
            {
                cur_track = left[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "right";
        }
        else if (direction == "right")
        {
            for (int i = 0; i < right.size(); i++)
            {
                cur_track = right[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }

    cout<<"Total number of seek operations = " << seek_count << endl;
    cout<< "Seek Sequence is" << endl;

    for (int i = 0; i < seek_sequence.size(); i++)
    {
        cout << seek_sequence[i] << endl;
    }
}

void CSCAN(int arr[], int head, int n)
{
    int seek_count = 0;
    int distance, cur_track;

    vector<int> left, right, seek_sequence;

    // Appending end values which has to be visited before reversing the direction
    left.push_back(0);
    right.push_back(disk_size - 1);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    // Sorting left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // First service the requests on the right side of the head.
    for (int i = 0; i < right.size(); i++)
    {
        cur_track = right[i];
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    // Once reached the right end jump to the beginning.
    head = 0;

    // Adding seek count for head returning from disk_size - 1 to 0
    seek_count += (disk_size - 1);

    // Now service the requests again which are left.
    for (int i = 0; i < left.size(); i++)
    {
        cur_track = left[i];
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < seek_sequence.size(); i++)
        cout << seek_sequence[i] << endl;
}

int main()
{
    int arr[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int n = sizeof(arr) / sizeof(arr[0]);

    // Call FCFS
    cout << "FCFS" << endl;
    FCFS(arr, head, n);
    cout << endl;

    // Call shortestSeekTimeFirst
    cout << "SSTF" << endl;
    shortestSeekTimeFirst(arr, head, n);
    cout << endl;

    // Call SCANDisk
    cout << "SCAN" << endl;
    SCANDisk(arr, head, "left", n);
    cout << endl;

    // Call CSCAN
    cout << "C-SCAN" << endl;
    CSCAN(arr, head, n);
    cout << endl;

    return 0;
}
