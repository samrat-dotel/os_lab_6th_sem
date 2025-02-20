#include <stdio.h>

#define MAX_PROCESS 100

struct process
{
    int pid, burst_time, waiting_time, turnaround_time, remaining_time, arrival_time;
};

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
    }

    int quantum;
    printf("Enter the quantum: ");
    scanf("%d", &quantum);

    int time = 0, completed = 0;
    int queue[MAX_PROCESS], front = 0, rear = 0;
    int in_queue[MAX_PROCESS] = {0};

    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival_time == 0)
        {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (completed < n)
    {
        if (front < rear)
        {
            int i = queue[front++];
            if (p[i].remaining_time > quantum)
            {
                time += quantum;
                p[i].remaining_time -= quantum;
            }
            else
            {
                time += p[i].remaining_time;
                p[i].turnaround_time = time - p[i].arrival_time;
                p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                p[i].remaining_time = 0;
                completed++;
            }

            for (int j = 0; j < n; j++)
            {
                if (!in_queue[j] && p[j].arrival_time <= time && p[j].remaining_time > 0)
                {
                    queue[rear++] = j;
                    in_queue[j] = 1;
                }
            }

            if (p[i].remaining_time > 0)
                queue[rear++] = i;
        }
        else
        {
            time++;
            for (int j = 0; j < n; j++)
            {
                if (!in_queue[j] && p[j].arrival_time <= time && p[j].remaining_time > 0)
                {
                    queue[rear++] = j;
                    in_queue[j] = 1;
                }
            }
        }
    }

    printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}
