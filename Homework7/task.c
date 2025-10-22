#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

//sort by arrival time
void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

//sort by burst time
void sortByBurst(struct Process p[], int n, int start_time) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time <= start_time && p[j + 1].arrival_time <= start_time) {
                if (p[j].burst_time > p[j + 1].burst_time) {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
}

// FCFS
void FCFS(struct Process p[], int n) {
    sortByArrival(p, n);

    int current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\n=== First Come First Served (FCFS) ===\n");
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;  // CPU idle
        printf("| P%d ", p[i].pid);
        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;
        current_time += p[i].burst_time;
        p[i].turnaround_time = current_time - p[i].arrival_time;
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }
    printf("|\n");

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);
}

// SJF
void SJF(struct Process p[], int n) {
    struct Process temp[n];
    for (int i = 0; i < n; i++)
        temp[i] = p[i];

    int completed[n];
    for (int i = 0; i < n; i++) completed[i] = 0;

    int completed_count = 0, current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\n=== Shortest Job First (SJF) ===\n");
    printf("Gantt Chart: ");

    while (completed_count < n) {
        int idx = -1;
        int min_bt = 99999;

        for (int i = 0; i < n; i++) {
            if (temp[i].arrival_time <= current_time && !completed[i]) {
                if (temp[i].burst_time < min_bt) {
                    min_bt = temp[i].burst_time;
                    idx = i;
                }
                else if (temp[i].burst_time == min_bt && temp[i].arrival_time < temp[idx].arrival_time) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        printf("| P%d ", temp[idx].pid);

        temp[idx].waiting_time = current_time - temp[idx].arrival_time;
        temp[idx].response_time = temp[idx].waiting_time;
        current_time += temp[idx].burst_time;
        temp[idx].turnaround_time = current_time - temp[idx].arrival_time;
        completed[idx] = 1;
        completed_count++;

        total_wt += temp[idx].waiting_time;
        total_tat += temp[idx].turnaround_time;
        total_rt += temp[idx].response_time;
    }

    printf("|\n");
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               temp[i].pid, temp[i].arrival_time, temp[i].burst_time,
               temp[i].waiting_time, temp[i].turnaround_time, temp[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    FCFS(p, n);
    SJF(p, n);

    return 0;
}

