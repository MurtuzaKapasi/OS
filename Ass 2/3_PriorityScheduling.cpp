#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int priority;
    int bt;
    int at;
    int ct;
    int wt;
    int tat;
    int completed;
};


int main()
{
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;

    process p[n];

    float avg_wt = 0, avg_tat = 0;
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter priority , arrival time and burst time of process " << i + 1 << ": ";
        p[i].pid = i + 1;
        cin >> p[i].priority >> p[i].at >> p[i].bt;
        p[i].completed = 0;
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int index = -1;
        int maxPriority = -1;
        for (int i = 0; i < n; i++){
            // just find index and min value of min burst time
            if (p[i].at <= current_time && p[i].completed == 0)
            {
                if (p[i].priority > maxPriority){
                    maxPriority = p[i].priority;
                    index = i;
                }

                if (p[i].priority == maxPriority){
                    if (p[i].at < p[index].at){
                        maxPriority = p[i].priority;
                        index = i;
                    }
                }
            }
        }

        if (index != -1){
            p[index].ct = current_time + p[index].bt;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].completed = 1;
            completed++;
            current_time = p[index].ct;
        }
        else
            current_time++;
    }

    for(int i=0 ; i<n ; i++){
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    avg_tat = (float) total_tat / n;
    avg_wt = (float) total_wt / n;

    cout << "Priority PID\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0 ; i<n ; i++){
        cout <<p[i].priority << "\t"<< p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }

    cout<<"Average Turnaround time: "<<avg_tat<<endl;
    cout<<"Average waiting time: "<<avg_wt<<endl;
}