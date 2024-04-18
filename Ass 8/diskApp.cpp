#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// FIFO Disk Scheduling Algorithm
int fifo(const vector<int> &requests, int headPosition, vector<int> &sequence) {
  int seekTime = 0;
  int currentHead = headPosition;
  for (int i = 0; i < requests.size(); i++) {
    sequence.push_back(requests[i]);
    seekTime += abs(currentHead - requests[i]);
    currentHead = requests[i];
  }
  return seekTime;
}

// SSTF Disk Scheduling Algorithm
int sstf(const vector<int> &requests, int headPosition, vector<int> &sequence) {
  vector<int> Requests = requests;
  sort(Requests.begin(), Requests.end());
  int seekTime = 0;
  int currentHead = headPosition;
  while (!Requests.empty()) {
    int closestRequest = Requests.front();
    int minDistance = abs(currentHead - closestRequest);
    int closestIndex = 0;
    for (int i = 1; i < Requests.size(); ++i) {
      int distance = abs(currentHead - Requests[i]);
      if (distance < minDistance) {
        minDistance = distance;
        closestRequest = Requests[i];
        closestIndex = i;
      }
    }
    sequence.push_back(closestRequest);
    seekTime += minDistance;
    currentHead = closestRequest;
    Requests.erase(Requests.begin() + closestIndex);
  }
  return seekTime;
}


// SCAN Disk Scheduling Algorithm
int scan (vector<int>&requests,int headPosition,int maxCylinder, vector<int>&sequence){
  vector<int>Requests(requests);
  int seekTime = 0;
  int currentHead = headPosition;
  sort(Requests.begin(),Requests.end());
  int currentIndex = 0;

  for(int i=0;i<Requests.size();i++){
    if(Requests[i]>currentHead){
      currentIndex = i;
      break;
    }
  }
  // travel in right direction
  for(int i=currentIndex;i<Requests.size();i++){
    sequence.push_back(Requests[i]);
    seekTime += abs(currentHead-Requests[i]);
    currentHead = Requests[i];
  }
  sequence.push_back(maxCylinder);
  seekTime += abs(currentHead-maxCylinder);
  currentHead=maxCylinder;
  // travel in left direction
  for(int i=currentIndex-1;i>=0;i--){
    sequence.push_back(Requests[i]);
    seekTime += abs(currentHead-Requests[i]);
    currentHead=Requests[i];
  }
  return seekTime;
}


int cscan(vector<int>& requests,int headPosition,int maxCylinder,vector<int>& sequence){
  vector<int> Requests(requests);
  int seekTime=0;
  int currentHead = headPosition;
  int currentIndex=0;
  sort(Requests.begin(),Requests.end());
  // find immediate request greater than headPosition
  for(int i=0;i<Requests.size();i++){
    if(Requests[i]>currentHead){
      currentIndex=i;
      break;
    }
  }
  // move to right
  for(int i=currentIndex;i<Requests.size();i++){
    sequence.push_back(Requests[i]);
    seekTime += abs(currentHead-Requests[i]);
    currentHead = Requests[i];
  }
  sequence.push_back(maxCylinder);
  seekTime += abs(currentHead - maxCylinder);
  currentHead = maxCylinder;
  sequence.push_back(0);
  seekTime += abs(currentHead-0);
  currentHead=0;
  //move to left
  for(int i=0;i<currentIndex;i++){
    sequence.push_back(Requests[i]);
    seekTime += abs(currentHead-Requests[i]);
    currentHead = Requests[i];
  }
return seekTime;
}

int main() {
  cout << "Enter the number of requests: ";
  // cin >> size;
    int arr[] = {98, 183, 37, 122, 14, 124, 65, 67};
  int size = sizeof(arr) / sizeof(arr[0]);
  cout << "Enter the requests: ";
  // for (int i = 0; i < size; ++i) {
    // cin >> arr[i];
  // }
  int head = 53 , maxCylinder = 200;
  // cout << "Enter the initial head position: ";
  // cin >> head;
  // cout << "Enter the maximum cylinder size: ";
  // cin >> maxCylinder;
  vector<int> requests(arr, arr + size);
  vector<int> sequence;
  cout << "Initial position of head: " << head << endl << endl;
  cout << "FIFO Seek Time: " << fifo(requests, head, sequence) << endl;
  cout << "Sequence: ";
  for (int i = 0; i < sequence.size(); i++) {
    cout << sequence[i] << "->";
  }
  cout << endl << endl;
  sequence.clear();

  cout << "SSTF Seek Time: " << sstf(requests, head, sequence) << endl;
  cout << "Sequence: ";
  for (int i = 0; i < sequence.size(); i++) {
    cout << sequence[i] << "->";
  }
  cout << endl << endl;
  sequence.clear();

  cout << "SCAN Seek Time: " << scan(requests, head,maxCylinder-1, sequence)
       << endl;
  cout << "Sequence: ";
  for (int i = 0; i < sequence.size(); i++) {
    cout << sequence[i] << "->";
  }
  cout << endl;
  sequence.clear();
  cout << endl;
  cout << "CSCAN Seek Time: " << cscan(requests, head, maxCylinder-1, sequence)<<endl;
  cout << "Sequence: ";
  for (int i = 0; i < sequence.size(); i++) {
    cout << sequence[i] << "->";
  }
 
  return 0;
}
