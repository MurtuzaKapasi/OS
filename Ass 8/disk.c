#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_REQUESTS 1000
#define MAX_TRACKS 10000
// Function to sort array in ascending order
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// Function to find index of nearest track
int findNearest(int tracks[], int n, int head)
{
    int minDist = abs(tracks[0] - head);
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        int dist = abs(tracks[i] - head);
        if (dist < minDist)
        {
            minDist = dist;
            index = i;
        }
    }
    return index;
}
// Function to implement FIFO scheduling algorithm
void fifo(int requests[], int n, int head)
{
    int totalSeek = 0;
    for (int i = 0; i < n; i++)
    {
        totalSeek += abs(head - requests[i]);
        head = requests[i];
    }
    printf("FIFO: Total Seek Time = %d\n", totalSeek);
}
// Function to implement SSTF scheduling algorithm
void sstf(int requests[], int n, int head)
{
    int totalSeek = 0;
    bool visited[MAX_REQUESTS] = {false};
    for (int i = 0; i < n; i++)
    {
        int minDist = MAX_TRACKS;
        int index = -1;
        for (int j = 0; j < n; j++)
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
    printf("SSTF: Total Seek Time = %d\n", totalSeek);
}
// Function to implement SCAN scheduling algorithm
void scan(int requests[], int n, int head, int maxTrack)
{
    int totalSeek = 0;
    bubbleSort(requests, n);
    int idx;
    for (idx = 0; idx < n; idx++)
    {
        if (requests[idx] > head)
            break;
    }
    totalSeek += abs(head - requests[idx]);
    head = requests[idx];
    for (int i = idx; i < n; i++)
    {
        totalSeek += abs(head - requests[i]);
        head = requests[i];
    }
    totalSeek += abs(maxTrack - head);
    head = maxTrack;
    printf("SCAN: Total Seek Time = %d\n", totalSeek);
}
// Function to implement C-SCAN scheduling algorithm
void cscan(int requests[], int n, int head, int maxTrack)
{
    int totalSeek = 0;
    bubbleSort(requests, n);
    int idx;
    for (idx = 0; idx < n; idx++)
    {
        if (requests[idx] > head)
            break;
    }
    totalSeek += abs(head - requests[idx]);
    head = requests[idx];
    for (int i = idx; i < n; i++)
    {
        totalSeek += abs(head - requests[i]);
        head = requests[i];
    }
    totalSeek += abs(0 - head);
    head = 0;
    totalSeek += abs(maxTrack - head);
    head = maxTrack;
    printf("C-SCAN: Total Seek Time = %d\n", totalSeek);
}
int main()
{
    int requests[MAX_REQUESTS];
    int n, head, maxTrack;
    // Input number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    // Input disk requests
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }
    // Input current head position
    printf("Enter the current head position: ");
    scanf("%d", &head);
    // Input maximum track number
    printf("Enter the maximum track number: ");
    scanf("%d", &maxTrack);
    fifo(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, maxTrack);
    cscan(requests, n, head, maxTrack);
    return 0;
}