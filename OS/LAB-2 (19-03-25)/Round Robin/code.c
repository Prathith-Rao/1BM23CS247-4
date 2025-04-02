
#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, bt, at, ct, wt, tat, remaining_bt;
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

void roundRobin(struct Process p[], int n, int quantum) {
    sortByArrivalTime(p, n);

    int completed = 0, time = 0;
    while (completed < n) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0 && p[i].at <= time) {
                done = false;
                if (p[i].remaining_bt > quantum) {
                    time += quantum;
                    p[i].remaining_bt -= quantum;
                } else {
                    time += p[i].remaining_bt;
                    p[i].ct=time;
                    p[i].tat = time - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    p[i].remaining_bt = 0;
                    completed++;
                }
            }
        }
        if (done) time++;
    }
}

void display(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, quantum;
    struct Process p[20];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT and BT of process %d: ", p[i].id);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].remaining_bt = p[i].bt;
    }

    printf("Enter Quantum Time: ");
    scanf("%d", &quantum);

    roundRobin(p, n, quantum);
    display(p, n);

    return 0;
}
