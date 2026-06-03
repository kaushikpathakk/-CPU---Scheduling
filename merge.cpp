#include <iostream>
#include <vector>

using namespace std;



class Process
{
public:
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turn Around Time
    int wt;   // Waiting Time
    int id;   // Process ID
    bool completed; // SJF ke liye flag

    
    void input(int i)
    {
        id = i;
        cout << "Enter AT and BT of Process P" << id << " : ";
        cin >> at >> bt;
        completed = false;
    }
};

/*
    FCFS Scheduling Algorithm
*/
void FCFS(vector<Process> p)
{
    
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = 0; j < p.size() - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
                swap(p[j], p[j + 1]);
        }
    }

    int time = 0;
    int idle = 0;

    cout << "\n--- FCFS Gantt Chart ---\n| ";

    for (int i = 0; i < p.size(); i++)
    {
        if (time < p[i].at)
        {
            cout << "Idle | ";
            idle += (p[i].at - time);
            time = p[i].at;
        }

        cout << "P" << p[i].id << " | ";

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
    }

    cout << "\n0";

    time = 0;
    for (int i = 0; i < p.size(); i++)
    {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        cout << "   " << time;
    }

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < p.size(); i++)
    {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "\nAvg TAT: " << totalTAT / p.size();
    cout << "\nAvg WT: " << totalWT / p.size();
    cout << "\nIdle Time: " << idle << endl;
}

/*
    SJF (Non-Preemptive)
*/
void SJF(vector<Process> p)
{
    int time = 0;
    int completed = 0;
    int n = p.size();

    cout << "\n--- SJF Gantt Chart ---\n| ";

    while (completed < n)
    {
        int idx = -1;
        int minBT = 1e9;

        
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed && p[i].at <= time)
            {
                if (p[i].bt < minBT)
                {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

       
        if (idx == -1)
        {
            time++;
            cout << "Idle | ";
            continue;
        }

        cout << "P" << p[idx].id << " | ";

        p[idx].ct = time + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        time = p[idx].ct;
        p[idx].completed = true;
        completed++;
    }

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "\nAvg TAT: " << totalTAT / n;
    cout << "\nAvg WT: " << totalWT / n << endl;
}


int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // input phase
    for (int i = 0; i < n; i++)
        p[i].input(i + 1);

    int choice;

    cout << "\nCPU Scheduling Algorithms\n";
    cout << "1. FCFS\n2. SJF\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
        FCFS(p);
    else if (choice == 2)
        SJF(p);
    else
        cout << "Invalid Choice";

    return 0;
}