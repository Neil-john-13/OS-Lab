#include <stdio.h>
#include <stdlib.h>

#define QUANTUM_TIME 2

int no_of_processes = 0;
struct Process
{
	int id;
	int arrival_time;
	int burst_time;
	int wait_time;
	int turn_around_time;
	int priority;
	int processed;
	int remainingTime;
    int completionTime;
};

struct Process sc[100];

void SJF ( struct Process sc[100])
{
   int time = 0;
	int processed = 0;
	int total_wait_time = 0;
	int total_turn_around_time = 0;
	while(processed != no_of_processes)
	{
		int shortest=-1;
		for (int i = 0; i < no_of_processes; i++)
		{
			if(sc[i].processed == 1)
			{ 
				continue;
			}
			if(sc[i].arrival_time <= time) {
				if(shortest == -1) {
					shortest = i;
				}
				else if(sc[i].burst_time < sc[shortest].burst_time) {
					shortest = i;
				}
			}
			else
			{
				break;
			}
			
		}
		if (shortest == -1) {
			for (int i = 0; i < no_of_processes; i++)
			{
				if(sc[i].processed == 0) {
					shortest = i;
					break;
				}
			}
		}
		if(sc[shortest].arrival_time > time) {
			time = sc[shortest].arrival_time;
		}
		else {
			sc[shortest].wait_time = time - sc[shortest].arrival_time;
			total_wait_time+=sc[shortest].wait_time;
			time += sc[shortest].burst_time;
			sc[shortest].turn_around_time = time - sc[shortest].arrival_time;
			total_turn_around_time+=sc[shortest].turn_around_time;
			sc[shortest].processed = 1;
			processed++;
		}
		
	}
		
	printf("\n\n\nPROCESS ID\tWAIT TIME\tTURN AROUND TIME\n");
	for (int i = 0; i < no_of_processes; i++)
	{
		printf("%d\t\t%d\t\t%d\n", sc[i].id, sc[i].wait_time, sc[i].turn_around_time);
	}


	printf("\n\nAVERAGE WAITING TIME: %d", total_wait_time/no_of_processes);
	printf("\n\nAVERAGE TURN AROUND TIME: %d", total_turn_around_time/no_of_processes);
}
void Priority(struct Process sc[100])
{
	int time = 0;
	int processed = 0;
	int total_wait_time = 0;
	int total_turn_around_time = 0;
	while(processed != no_of_processes)
	{
		int shortest=-1;
		for (int i = 0; i < no_of_processes; i++)
		{
			if(sc[i].processed == 1)
			{ 
				continue;
			}
			if(sc[i].arrival_time <= time) {
				if(shortest == -1) {
					shortest = i;
				}
				else if(sc[i].priority < sc[shortest].priority) {
					shortest = i;
				}
			}
		}
		if (shortest == -1) {
			for (int i = 0; i < no_of_processes; i++)
			{
				if(sc[i].processed == 0) {
					shortest = i;
					break;
				}
			}
		}
		if(sc[shortest].arrival_time > time) {
			time = sc[shortest].arrival_time;
		}
		else {
			sc[shortest].wait_time = time - sc[shortest].arrival_time;
			total_wait_time+=sc[shortest].wait_time;
			time += sc[shortest].burst_time;
			sc[shortest].turn_around_time = time - sc[shortest].arrival_time;
			total_turn_around_time+=sc[shortest].turn_around_time;
			sc[shortest].processed = 1;
			processed++;
		}
		
	}
		
	printf("\n\n\nPROCESS ID\tWAIT TIME\tTURN AROUND TIME\n");
	for (int i = 0; i < no_of_processes; i++)
	{
		printf("%d\t\t%d\t\t%d\n", sc[i].id, sc[i].wait_time, sc[i].turn_around_time);
	}


	printf("\n\nAVERAGE WAITING TIME: %d", total_wait_time/no_of_processes);
	printf("\n\nAVERAGE TURN AROUND TIME: %d", total_turn_around_time/no_of_processes);

}

void rr(struct Process sc[100])
{
	int time = 0;
	int processed = 0;
	int total_wait_time = 0;
	int total_turn_around_time = 0;
	int count=0;
    while (count < no_of_processes) {
        for (int i = 0; i < no_of_processes; i++) {
            if (sc[i].remainingTime > 0) {
                if (sc[i].remainingTime > QUANTUM_TIME) {
                    time += QUANTUM_TIME;
                    sc[i].remainingTime -= QUANTUM_TIME;
                } else {
                    time += sc[i].remainingTime;
                    sc[i].completionTime = time;
                    sc[i].turn_around_time = sc[i].completionTime - sc[i].arrival_time;
                    sc[i].wait_time = sc[i].turn_around_time - sc[i].burst_time;
                    total_turn_around_time+= sc[i].turn_around_time;
                    total_wait_time += sc[i].wait_time;
                    sc[i].remainingTime = 0;
                    count++;
                }
            }
        }
	}
	printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < no_of_processes; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", sc[i].id, sc[i].arrival_time, sc[i].burst_time, sc[i].priority, sc[i].turn_around_time, sc[i].wait_time);
    }

    // Output average turnaround time and waiting time
    int avgTurnaroundTime = (float) total_turn_around_time/ no_of_processes;
    int avgWaitingTime = (float) total_wait_time/ no_of_processes;
    printf("\nAverage Turnaround Time = %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time = %.2f\n", avgWaitingTime);
}

void main() {
	int choice;
	printf("Enter number of processes to enter: ");
	scanf("%d", &no_of_processes);
	for (int i = 0; i < no_of_processes; i++)
	{
		printf("Enter Process ID: ");
		scanf("%d", &sc[i].id);
		printf("Enter Process Arival Time: ");
		scanf("%d", &sc[i].arrival_time);
		printf("Enter Process Burst Time: ");
		scanf("%d", &sc[i].burst_time);
		printf("Enter Process priority: ");
		scanf("%d", &sc[i].priority);
		sc[i].processed = 0;
		sc[i].remainingTime = sc[i].burst_time;
	}



    for (int i = 0; i < no_of_processes; i++)
	{
		for (int j = 0; j < no_of_processes - i - 1; j++)
		{
			if(sc[j].arrival_time > sc[j + 1].arrival_time) {
				struct Process temp = sc[j + 1];
				sc[j + 1] = sc[j];
				sc[j] = temp;
			}
		}
	}

    printf("\nPROCESS ID\tARRIVAL TIME\tBURST TIME\tPRIORITY\n");
	for (int i = 0; i < no_of_processes; i++)
	{
		printf(" %d\t\t%d\t\t%d\t\t%d\n", sc[i].id, sc[i].arrival_time, sc[i].burst_time,sc[i].priority);
	}

	while (1)
	{
		printf("\n1. FCFS 2. SJF 3. Priority 4. Round Robin 5. Exit \nEnter your choice :");
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:
				break;
			case 2:
				SJF(sc);
				break;
			case 3:
				Priority(sc);
				break;
			case 4:
				rr(sc);
				break;
			case 5 :
				exit(0);
			default:
				printf("Invalid choice");
		}
	}
}