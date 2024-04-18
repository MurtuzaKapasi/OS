#include <bits/stdc++.h>

using namespace std;

const int disk_size = 200;

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
        cout << arr[i] << " ";
}

void shortestSeekTimeFirst(int request[], int head, int n)
{
    vector<int> req(n) ;
    vector<int> seek_sequence;

    if (n == 0)
        return;
    for(int i=0 ; i<n ; i++)
        req[i] = request[i];

    sort(req.begin(),req.end());

    int seek_dist = 0;
    int currentHead = head;
    int index = -1 , closestReq =0 ;

    while(!req.empty()){
        closestReq = req.front();
        index = 0;
        int minDiff = abs(closestReq - currentHead);
        for(int i=1 ; i<req.size() ; i++){
            int diff = abs(req[i] - currentHead);
            if(diff < minDiff){
                minDiff = diff;
                closestReq = req[i];
                index = i;
            }
        }

        seek_sequence.push_back(closestReq);
        currentHead = closestReq;
        seek_dist += minDiff;
        req.erase(req.begin() + index);
    }
   
cout<<"Total number of seek operations = "<<seek_dist<<endl;

    // print the sequence
    for (int i = 0; i < n; i++)
       cout << seek_sequence[i] << " "; 
}

void SCANDisk(int arr[], int head, string direction, int n)
{
    int seek_dist = 0;
    int distance, cur_track , index = -1;
    vector<int> req , seek_sequence;

    for (int i = 0; i < n; i++)
        req.push_back(arr[i]);

    sort(req.begin(), req.end());
    int currentHead = head;
    //getting index just greater than head
    for(int i=0 ; i< n ; i++){
        if(req[i] > head){
            index = i;
            break;
        }
    }

    //traversing right upto end
    for(int i=index ; i<n ; i++){
        seek_sequence.push_back(req[i]);
        seek_dist += abs(currentHead - req[i]);
        currentHead  = req[i];
    }

    seek_sequence.push_back(disk_size - 1);
    seek_dist+= abs(currentHead - (disk_size - 1));
    currentHead = disk_size -1;

    //traversing to left
    for(int i= index-1 ; i>=0 ; i--){
        seek_sequence.push_back(req[i]);
        seek_dist += abs(currentHead - req[i]);
        currentHead = req[i];
    }

    cout<<"Total number of seek operations = "<<seek_dist<<endl;

    // print the sequence
    for (int i = 0; i < seek_sequence.size(); i++)
       cout << seek_sequence[i] << " "; 

}

void CSCAN(int arr[], int head, int n)
{
    int seek_count = 0;
    int distance, cur_track;

    vector<int>  seek_sequence , req;
    for(int i=0 ; i<n ; i++)
        req.push_back(arr[i]);

    sort(req.begin(),req.end());

    int index = 0;
    for(int i=0 ; i<n ; i++){
        if(req[i] > head){
            index = i;
            break;
        }
    }

    for(int i=index ; i<n ; i++){
        seek_sequence.push_back(req[i]);
        seek_count += abs(head - req[i]);
        head = req[i];
    }

    seek_sequence.push_back(disk_size - 1);
    seek_count += abs(head - (disk_size - 1));
    head = disk_size - 1;

    seek_sequence.push_back(0);
    seek_count += abs(head - 0);
    head = 0;

    for(int i=0 ; i<index; i++){
        seek_sequence.push_back(req[i]);
        seek_count += abs(head - req[i]);
        head = req[i];
    }

    cout<<"Total number of seek operations = "<<seek_count<<endl;

    for (int i = 0; i < seek_sequence.size(); i++)
        cout << seek_sequence[i] << " ";
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
