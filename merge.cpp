#include <iostream>
using namespace std;
// int time = 0;
class Process
{
public:
    int at, bt, ct, tat, wt, id, completed;
    void input(int i)
    {
        id = i;
        cout << " Enter the value of AT and BT of process " << id << endl;
        cin >> at >> bt;
    }
};
void CalculateSJF(Process p[], int n)
{
    int time = 0;
    int completed = 0;
    int idle_time = 0;
    float total_tat = 0, total_wt = 0;
    while (completed < n)
    {
        int idx = -1;
        int minbt = 99999;

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
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            time = p[idx].ct;
            p[idx].completed = 1;
            completed++;
        }
         
        cout << "\nGantt Chart:\n| ";

        if (idx == -1)
        {
            cout << "idle | ";
            time++;
            idle_time++;
        }
        else
        {
            cout << "P" << p[idx].id << " | ";

            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            time = p[idx].ct;
            p[idx].completed = 1;
            completed++;
        }
        cout << "\n0 ";
        time = 0;

        while (true)
        {
            int done = 1;

            for (int i = 0; i < n; i++)
            {
                if (p[i].completed == 0)
                {
                    done = 0;
                }
            }

            if (done)
                break;

            int idx = -1;
            int minbt = 99999;

            for (int i = 0; i < n; i++)
            {
                if (p[i].at <= time && p[i].completed == 0)
                {
                    if (idx == -1 || p[i].bt < minbt || (p[i].bt == minbt && p[i].at < p[idx].at))
                    {
                        minbt = p[i].bt;
                        idx = i;
                    }    
                }
            }

            if (idx == -1)
            {
                time++;
                cout << "   " << time;
            }
            else
            {
                time += p[idx].bt;
                cout << "   " << time;
                p[idx].completed = 1;
            }
        }
    }

    cout << " Idle Time :" << idle_time << endl;
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
}

void CalculateFCFS(Process p[], int n)
{

    // sort by arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                swap(p[j], p[j + 1]);
            }
        }
    }

    int time = 0;
    int idle_time = 0;
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {

        if (time < p[i].at)
        {
            idle_time += (p[i].at - time);
            time = p[i].at;
        }

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
    }

    float cpu_util = ((float)(time - idle_time) / time) * 100;
    float throughput = (float)n / time;

    cout << "Throughput: " << throughput << endl;
    cout << "Idle Time: " << idle_time << endl;
    cout << "CPU Utilisation: " << cpu_util << "%\n";

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

    cout << "\nGantt Chart:\n| ";
    for (int i = 0; i < n; i++)
    {

        if (time < p[i].at)
        {
            cout << "idle | ";
            idle_time += (p[i].at - time);
            time = p[i].at;
        }

        // Gantt chart
        cout << "P" << p[i].id << " | ";

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
    }
    cout << "\n0 ";
    time = 0;

    for (int i = 0; i < n; i++)
    {

        if (time < p[i].at)
        {
            cout << "   " << p[i].at;
            time = p[i].at;
        }

        time += p[i].bt;
        cout << "   " << time;
    }
    cout << endl;
}

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
    cout << " CPU SCHEDULING " << endl;
    cout << " Enter 1 for FCFS and 2 for SJF " << endl;
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