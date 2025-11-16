#include <stdio.h>

typedef struct
{
    int pid, at, bt, st, ct, tat, wt;
} Process;

int main()
{
    int n;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort by arrival time (simple bubble sort)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at)
            {
                Process t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
            }

    // Calculations
    for (int i = 0; i < n; i++)
    {
        p[i].st = (i == 0 || p[i - 1].ct < p[i].at) ? p[i].at : p[i - 1].ct;
        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    // Output
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++)
        printf(" P%d |", p[i].pid);

    printf("\n\nPID\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].st, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
}
