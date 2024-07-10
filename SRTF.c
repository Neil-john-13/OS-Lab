#include <stdio.h>
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};


int main() {
    int n, total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process processes[10];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    int current_time = 0, completed = 0;
    while (completed < n) {
        int shortest_remaining_time = 999999, shortest_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_remaining_time && processes[i].remaining_time > 0) {
                shortest_remaining_time = processes[i].remaining_time;
                shortest_index = i;
            }
        }
        if (shortest_index == -1) {
            current_time++;
            continue;
        }
        processes[shortest_index].remaining_time--;
        if (processes[shortest_index].remaining_time == 0) {
            completed++;
            processes[shortest_index].completion_time = current_time + 1;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            total_waiting_time += processes[shortest_index].waiting_time;
            total_turnaround_time += processes[shortest_index].turnaround_time;
        }
        current_time++;
    }
    printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("Average waiting time: %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time / n);
    return 0;
}
