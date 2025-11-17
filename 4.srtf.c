#include <stdio.h>

int main()
{
	int n, completed = 0, curr = 0;
	int at[5], bt[5], rt[5], ct[5], tat[5], wt[5], comp[5] = {0};
	float avgwt = 0, avgtat = 0;

	printf("\nEnter number of processes (less than 5): ");
	scanf("%d", &n);

	printf("\nEnter arrival times:\n");
	for (int i = 0; i < n; i++)
	{
		printf("Process %d: ", i + 1);
		scanf("%d", &at[i]);
	}

	printf("\nEnter burst times:\n");
	for (int i = 0; i < n; i++)
	{
		printf("Process %d: ", i + 1);
		scanf("%d", &bt[i]);
		rt[i] = bt[i];
	}

	while (completed < n)
	{
		int min = 999, idx = -1;
		for (int i = 0; i < n; i++)
		{
			if (at[i] <= curr && !comp[i] && rt[i] < min)
			{
				min = rt[i];
				idx = i;
			}
		}

		if (idx != -1)
		{
			rt[idx]--;
			if (rt[idx] == 0)
			{
				comp[idx] = 1;
				completed++;
				ct[idx] = curr + 1;
				tat[idx] = ct[idx] - at[idx];
				wt[idx] = tat[idx] - bt[idx];
				avgtat += tat[idx];
				avgwt += wt[idx];
			}
		}
		curr++;
	}

	printf("\nArrival\tBurst\tComp\tTurnaround\tWaiting");
	for (int i = 0; i < n; i++)
		printf("\n%d\t%d\t%d\t%d\t\t%d", at[i], bt[i], ct[i], tat[i], wt[i]);

	printf("\nAverage Waiting Time = %.2f", avgwt / n);
	printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);

	return 0;
}
