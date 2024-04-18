// program tom implement FCFS scheduling algo
#include<bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int bt;
    int at;
    int ct;
    int wt;
    int tat;
};

bool compareArrival(process p1,process p2){
    if(p1.at == p2.at)
        return p1.pid < p2.pid;
    return p1.at < p2.at;
}
bool compareProcess(process p1,process p2){
    return p1.pid < p2.pid;
}

int main()
{
    int n;
    cout<<"Enter no. of processes: ";
    cin>>n;

    process p[n];
    float avg_wt=0,avg_tat=0;
    int total_wt=0,total_tat=0;

    for(int i=0 ; i<n ; i++)
    {
        cout<<"Enter arrival time and burst time of process "<<i+1<<": ";
        p[i].pid=i+1;
        cin>>p[i].at>>p[i].bt;
    }

    sort(p,p+n,compareArrival);

    // for finding completion time
    int start=0;
    for(int i=0 ; i<n ; i++){
        if(i==0)
            start=p[i].bt + p[i].at;
        else if(p[i-1].ct < p[i].at){
            start = p[i].bt + p[i].at ;
        }
        else
            start = p[i-1].ct + p[i].bt;
        p[i].ct = start;
    }

    // for turnaround time and waiting time
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // for finding total waiting time and total turnarround time
    total_tat=0;
    total_wt=0;
    for(int i=0 ; i<n ; i++){
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    sort(p,p+n,compareProcess);

    // for printing the table
    cout<<"pid\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0 ; i<n ; i++){
        cout<<p[i].pid<<" \t"<<p[i].at<<" \t"<<p[i].bt<<"\t "<<p[i].ct<<" \t"<<p[i].tat<<" \t"<<p[i].wt<<endl;
    }

    avg_tat = float(total_tat)/n;
    avg_wt = float(total_wt)/n;

    cout<<"Average turnaround time : \t"<<avg_tat<<endl;
    cout<<"Average waiting time : \t"<<avg_wt<<endl;

}