#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int bt;
    int at;
    int ct;
    int wt;
    int tat;
    int completed;
};

bool compareArrival(process p1, process p2)
{
    if (p1.at == p2.at)
        return p1.pid < p2.pid;
    return p1.at < p2.at;
}

bool compareProcess(process p1, process p2)
{
    return p1.pid < p2.pid;
}

void fcfsScheduling(process p[], int n)
{
    float avg_wt = 0, avg_tat = 0;
    int total_wt = 0, total_tat = 0;

    sort(p, p + n, compareArrival);

    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (p[i].at > current_time)
            current_time = p[i].at;
        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        current_time = p[i].ct;
    }

    for (int i = 0; i < n; i++)
    {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    avg_tat = (float)total_tat / n;
    avg_wt = (float)total_wt / n;

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }

    cout << "Average Turnaround time: " << avg_tat << endl;
    cout << "Average waiting time: " << avg_wt << endl;
}

void sjfScheduling(process p[], int n)
{
    float avg_wt = 0, avg_tat = 0;
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int index = -1;
        int min = 99999999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && p[i].completed == 0)
            {
                if (p[i].bt < min)
                {
                    min = p[i].bt;
                    index = i;
                }

                if (p[i].bt == min)
                {
                    if (p[i].at < p[index].at)
                    {
                        min = p[i].bt;
                        index = i;
                    }
                }
            }
        }

        if (index != -1)
        {
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

    for (int i = 0; i < n; i++)
    {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    avg_tat = (float)total_tat / n;
    avg_wt = (float)total_wt / n;

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }

    cout << "Average Turnaround time: " << avg_tat << endl;
    cout << "Average waiting time: " << avg_wt << endl;
}

int main()
{
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;

    process p[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time of process " << i + 1 << ": ";
        p[i].pid = i + 1;
        cin >> p[i].at >> p[i].bt;
    }

    int choice;
    cout << "Select scheduling algorithm:\n";
    cout << "1. First-Come, First-Served (FCFS)\n";
    cout << "2. Shortest Job First (SJF)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        fcfsScheduling(p, n);
        break;
    case 2:
        sjfScheduling(p, n);
        break;
    default:
        cout << "Invalid choice!\n";
    }

    return 0;
}
