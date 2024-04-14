#include <bits/stdc++.h>
using namespace std;
struct Process
{
    int AT, BT, ST[20], WT, FT, TAT, pos, RT;
};
int quant;
int main()
{
    int n, i, j;
    // Taking Input
    cout << "Enter the no. of processes: ";
    cin >> n;
    Process p[n];
    cout << "Enter time quantum: ; " << endl;
    cin >> quant;
    cout << "Enter the Arrival time and burst time  of processes:   " << endl;
    for (i = 0; i < n; i++)
    {   p[i].pos = i+1;
        cin >> p[i].AT >> p[i].BT;
    }
    // Declaring variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];
    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++)
    {
        b[i] = p[i].BT;

        a[i] = p[i].AT;
        for (j = 0; j < 20; j++)
        {
            s[i][j] = -1;
        }
    }
    int tot_wt, tot_tat, tot_rt;
    tot_wt = tot_tat = tot_rt = 0;
    bool flag = false;
    while (c != 0)
    {
        mini = INT_MAX;
        flag = false;
        for (i = 0; i < n; i++)
        {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0)
            {
                index = i;
                mini = a[i];
                flag = true;
            }
        }
        // if at =1 then loop gets out hence set flag to false
        if (!flag)
        {
            time++;
            continue;
        }
        // calculating start time
        j = 0;
        while (s[index][j] != -1)
        {
            j++;
        }
        if (s[index][j] == -1)
        {
            s[index][j] = time;
            p[index].ST[j] = time;
        }
        if (b[index] <= quant)
        {
            time += b[index];
            b[index] = 0;
        }
        else
        {
            time += quant;
            b[index] -= quant;
        }
        if (b[index] > 0)
        {
            a[index] = time + 0.1;
        }
        // calculating arrival, burst, final times
        if (b[index] == 0)
        {
            c--;
            p[index].FT = time;
            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
            tot_wt += p[index].WT;
            p[index].TAT = p[index].BT + p[index].WT;
            tot_tat += p[index].TAT;
            p[index].RT = p[index].ST[0] - p[index].AT;
            tot_rt += p[index].RT;
        }
    } // end of while loop
    // Printing output
    cout << "Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (i = 0; i < n; i++)
    {
        cout << p[i].pos << "\t" << p[i].AT << "\t" << p[i].BT << "\t" << p[i].FT << "\t" << p[i].TAT << "\t" << p[i].WT << "\t" << p[i].RT << endl;
    }
    // Calculating average wait time, turnaround time, and response time
    double avg_wt, avg_tat, avg_rt;
    avg_wt = static_cast<double>(tot_wt) / n;
    avg_tat = static_cast<double>(tot_tat) / n;
    avg_rt = static_cast<double>(tot_rt) / n;
    // Printing average wait time, turnaround time, and response time

    cout << "\nAverage Wait Time: " << avg_wt << endl;
    cout << "Average Turnaround Time:" << avg_tat << endl;
    cout << "Average Response Time: " << avg_rt << endl;

    return 0;
}