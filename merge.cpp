#include <iostream>
using namespace std;

class Process
{
public:
    int at, bt, ct, tat, wt, id, completed;

    void input(int i)
    {
        id = i;
        cout << "Enter AT and BT of process " << id << endl;
        cin >> at >> bt;
    }
};

// ===================== SJF =====================
void CalculateSJF(Process p[], int n)
{
    int time = 0, completed = 0, idle_time = 0;
    float total_tat = 0, total_wt = 0;

    int order[50], k = 0; // store execution order

    while (completed < n)
    {
        int idx = -1, minbt = 99999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].completed == 0)
            {
                if (idx == -1 || p[i].bt < minbt ||
                    (p[i].bt == minbt && p[i].at < p[idx].at))
                {
                    minbt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            time++;
            idle_time++;
        }
        else
        {
            order[k++] = idx;

            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            time = p[idx].ct;
            p[idx].completed = 1;
            completed++;
        }
    }

    //  Gantt Chart
    cout << "\nGantt Chart:\n| ";
    for (int i = 0; i < k; i++)
        cout << "P" << p[order[i]].id << " | ";

    cout << "\n0 ";
    time = 0;

    for (int i = 0; i < k; i++)
    {
        int idx = order[i];

        if (time < p[idx].at)
            time = p[idx].at;

        time += p[idx].bt;
        cout << "   " << time;
    }
    cout << endl;

    // Result table
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    cout << "\nAverage TAT: " << total_tat / n << endl;
    cout << "Average WT: " << total_wt / n << endl;
    cout << "Idle Time: " << idle_time << endl;
}

// ===================== FCFS =====================
void CalculateFCFS(Process p[], int n)
{
    // sort by arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
                swap(p[j], p[j + 1]);
        }
    }

    int time = 0, idle_time = 0;
    float total_tat = 0, total_wt = 0;

    //  Gantt Chart
    cout << "\nGantt Chart:\n| ";

    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
        {
            cout << "idle | ";
            idle_time += (p[i].at - time);
            time = p[i].at;
        }

        cout << "P" << p[i].id << " | ";

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
    }

    // timeline
    cout << "\n0 ";
    time = 0;

    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
        {
            time = p[i].at;
            cout << "   " << time;
        }

        time += p[i].bt;
        cout << "   " << time;
    }
    cout << endl;

    // results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    cout << "\nAverage TAT: " << total_tat / n << endl;
    cout << "Average WT: " << total_wt / n << endl;
    cout << "Idle Time: " << idle_time << endl;
}

// ===================== MAIN =====================
int main()
{
    int n;
    cout << "Enter number of processes: " << endl;
    cin >> n;

    Process p[50];

    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
        p[i].input(i + 1);
    }

    int choice;
    cout << "\nCPU SCHEDULING\n";
    cout << "Enter 1 for FCFS and 2 for SJF\n";
    cin >> choice;

    Process temp[50];

    for (int i = 0; i < n; i++)
    {
        temp[i] = p[i];
        temp[i].completed = 0;
    }

    switch (choice)
    {
    case 1:
        CalculateFCFS(temp, n);
        break;

    case 2:
        CalculateSJF(temp, n);
        break;

    default:
        cout << "Invalid choice";
    }

    return 0;
}