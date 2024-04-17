#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct process {
  int pid, at, bt, rbt, ct, tat, wt, rt, complete, queue;
};

int tq;
vector<int> RQ;

bool compareArrival(process p1, process p2) {
  if (p1.at == p2.at)
    return p1.pid < p2.pid;
  return p1.at < p2.at;
}

bool compareProcess(process p1, process p2) { return p1.pid < p2.pid; }

int main() {
  int n, i;
  cout << "Enter the no. of processes: ";
  cin >> n;
  process p[n];

  cout << "Enter time quantum: ";
  cin >> tq;

  for (i = 0; i < n; i++) {
    cout << "Enter Arrival time and Burst time of process " << i + 1 << ": ";
    p[i].pid = i + 1;
    cin >> p[i].at >> p[i].bt;
    p[i].rbt = p[i].bt;
    p[i].complete = 0;
    p[i].rt = -1;
    p[i].queue = 0;
  }

  sort(p, p + n, compareArrival);

  int count = 0;
  int time = 0;

  float t_tat=0, t_wt=0, t_rt=0;

  while (count < n) {
    for (int i = 0; i < n && count < n; i++) {
      if (p[i].complete == 1)
        continue;

      if (RQ.empty()) {
        if (time < p[i].at)
          time = p[i].at;
        RQ.push_back(i);
        p[i].queue =1;
      }

      int idx = RQ.front();
      RQ.erase(RQ.begin());

      for(int j = idx+1; j < n; j++)
      {
        if(p[j].at <= time+min(p[idx].rbt,tq) && p[j].queue == 0)
        {
          RQ.push_back(j);
          p[j].queue = 1;
        }
      }

      if (p[idx].rt == -1)
        p[idx].rt = time - p[idx].at; // Update response time here


      if (p[idx].rbt <= tq) {
        time += p[idx].rbt;
        p[idx].rbt = 0;
        p[idx].ct = time;                   // Update completion time
        p[idx].tat = p[idx].ct - p[idx].at; // Update turnaround time
        p[idx].wt = p[idx].tat - p[idx].bt; // Update waiting time
        p[idx].complete = 1;
        t_tat += p[idx].tat;
        t_wt += p[idx].wt;
        t_rt += p[idx].rt;
        count++;
      } else {
        time += tq;
        p[idx].rbt -= tq;

        // Add the process back to the end of the ready queue
        RQ.push_back(idx);
      }
    }
  }

  sort(p, p + n, compareProcess);

  cout << "Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n";
  for (i = 0; i < n; i++) {
    cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct
         << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].rt << endl;
  }

  cout<<"Average TAT: "<<t_tat/n<<endl;
  cout<<"Average WT: "<<t_wt/n<<endl;
  cout<<"Average RT: "<<t_rt/n<<endl;
  return 0;
}