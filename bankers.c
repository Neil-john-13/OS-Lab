#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10


int isSafe(int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int nProcesses, int nResources)
{
    int i, j;
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (i = 0; i < nResources; i++)
        work[i] = available[i];


    for (i = 0; i < nProcesses; i++)
    {
        for (j = 0; j < nResources; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    int count = 0;
    int safeSequence[MAX_PROCESSES];
    
    while (count < nProcesses)
    {
        int found = 0;
        for (i = 0; i < nProcesses; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < nResources; j++)
                {
                    if (need[i][j] > work[j]||need[i][j]<0)
                        break;
                }
                if (j == nResources)
                {
    
                    for (j = 0; j < nResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0)
        {
            return 0;
        }
    }
    printf("Safe sequence: ");
    for (i = 0; i < nProcesses; i++)
    {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

int main()
{
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int nProcesses, nResources, i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &nProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &nResources);

    printf("Enter the available resources: ");
    for (i = 0; i < nResources; i++)
    {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resource matrix:\n");
    for (i = 0; i < nProcesses; i++)
    {
        for (j = 0; j < nResources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocated resource matrix:\n");
    for (i = 0; i < nProcesses; i++)
    {
        for (j = 0; j < nResources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

  
    if (isSafe(available, max, allocation, nProcesses, nResources))
    {
        printf("\nthe system is in a safe state");
    }
    else{
        printf("the system is in a un safe state");
    }

    printf("\n enter the process request : ");
    int request[MAX_RESOURCES];
    for (i = 0; i < nResources; i++)
    {
        scanf("%d", &request[i]);
    }
    int process_id,flag=0;
    printf("enter the process id :");
    scanf("%d",&process_id);


    for(int i=0;i<nResources;i++)
    {
        if(request[i]>( max[process_id][j] - allocation[process_id][i]) ||request[i]>available[i] )
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        for (j = 0; j < nResources; j++)
        {
            available[j]= available[j]-request[j];
            allocation[process_id][j]= allocation[process_id][j]+request[j];

        }
        if (isSafe(available, max, allocation, nProcesses, nResources))
        {
            printf("\nthe system is in a safe state");
        }
        else{
            printf("the system is in a un safe state");
        }
    }
    else{
        printf("access not Granted"); 
    }
}
