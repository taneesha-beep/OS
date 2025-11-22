#include <stdio.h>

int isSafe(int n, int m, int alloc[n][m], int need[n][m], int avail[m], int safeSeq[n])
{
    int finish[n], work[m], count = 0;
    for (int i = 0; i < m; i++)
        work[i] = avail[i];
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n)
    {
        int found = 0;
        for (int p = 0; p < n; p++)
        {
            if (!finish[p])
            {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            return 0; // unsafe
    }
    return 1; // safe
}

void inputMatrix(char *name, int n, int m, int mat[n][m])
{
    printf("\nEnter %s Matrix (%d x %d):\n", name, n, m);
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &mat[i][j]);
    }
}

void printMatrix(char *title, int n, int m, int mat[n][m])
{
    printf("\n%s:\n", title);
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main()
{
    int n, m;
    printf("Enter number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m], req[m], safeSeq[n];
    inputMatrix("Allocation", n, m, alloc);
    inputMatrix("Max", n, m, max);

    printf("\nEnter Available Resources (%d): ", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printMatrix("Need Matrix", n, m, need);

    if (isSafe(n, m, alloc, need, avail, safeSeq))
    {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d%s", safeSeq[i], (i == n - 1) ? "" : " -> ");
    }
    else
    {
        printf("\nSystem is NOT in a safe state.\n");
        return 0;
    }

    int p;
    printf("\n\nEnter process number making request (0-%d): ", n - 1);
    scanf("%d", &p);

    printf("Enter request vector for P%d: ", p);
    for (int i = 0; i < m; i++)
        scanf("%d", &req[i]);

    // Validate request
    for (int i = 0; i < m; i++)
    {
        if (req[i] > need[p][i])
            return printf("Error: Request exceeds process's need.\n"), 0;
        if (req[i] > avail[i])
            return printf("Resources not available. Process must wait.\n"), 0;
    }

    // Tentative allocation
    for (int i = 0; i < m; i++)
    {
        avail[i] -= req[i];
        alloc[p][i] += req[i];
        need[p][i] -= req[i];
    }

    if (isSafe(n, m, alloc, need, avail, safeSeq))
    {
        printf("\nRequest can be granted. System remains SAFE.\nNew Safe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d%s", safeSeq[i], (i == n - 1) ? "" : " -> ");
    }
    else
    {
        printf("\nRequest cannot be granted. Leads to UNSAFE state.\n");
        // Rollback
        for (int i = 0; i < m; i++)
        {
            avail[i] += req[i];
            alloc[p][i] -= req[i];
            need[p][i] += req[i];
        }
    }
    return 0;
}