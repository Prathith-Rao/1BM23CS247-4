#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, bt, at, ct, wt, tat, remaining_bt, priority;
};

void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void priorityNonPreemptive(struct Process p[], int n) {
    sortByArrivalTime(p, n);

    int completed = 0, time = 0;
    while (completed < n) {
        int idx = -1, highest = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining_bt > 0 && p[i].priority > highest) {
                highest = p[i].priority;
                idx = i;
            }
        }
        if (idx != -1) {
            time += p[idx].remaining_bt;
            p[idx].ct=time;
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].remaining_bt = 0;
            completed++;
        } else {
            time++;
        }
    }
}

void priorityPreemptive(struct Process p[], int n) {
    sortByArrivalTime(p, n);

    int completed = 0, time = 0;
    while (completed < n) {
        int idx = -1, highest = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining_bt > 0 && p[i].priority > highest) {
                highest = p[i].priority;
                idx = i;
            }
        }
        if (idx != -1) {
            p[idx].remaining_bt--;
            time++;
            if (p[idx].remaining_bt == 0) {
                completed++;
                p[idx].ct=time;
                p[idx].tat = time - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            time++;
        }
    }
}

void display(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("\nAverage WT: %f", total_wt / n);
    printf("\nAverage TAT: %f\n", total_tat / n);
}

int main() {
    int n, choice;
    struct Process p[20];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT,BT and Priority of process %d: ", p[i].id);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].remaining_bt = p[i].bt;
    }

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Priority Non-Preemptive\n2. Priority Preemptive\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            priorityNonPreemptive(p, n);
            display(p, n);
            break;
        case 2:
            priorityPreemptive(p, n);
            display(p, n);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}
