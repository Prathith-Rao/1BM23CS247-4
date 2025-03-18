#include<stdio.h>
#include<limits.h>
struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int remaining_bt;
};

void sortByArrival(struct Process p[],int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i;j++){
            if(p[j].at>p[j+1].at){
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void FCFS(struct Process p[], int n) {
    sortByArrival(p, n);
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at)
            currentTime = p[i].at;
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currentTime = p[i].ct;
    }
}


void SJF(struct Process p[],int n ){
    sortByArrival(p, n);
    int currentTime = 0;
    for (int i = 0; i < n; i++){
        int minIndex = i;
        for (int j = i + 1; j < n; j++ ){
            if(p[j].at<=currentTime && p[j].bt<p[minIndex].bt){
                minIndex = j;
            }
        }
        if(minIndex!=i){
            struct Process temp = p[i];
            p[i] = p[minIndex];
            p[minIndex] = temp;
        }
        if(currentTime<p[i].at){
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currentTime += p[i].bt;
    }
}

void SJF_Preemptive(struct Process p[],int n ){
    int complete = 0, currentTime = 0, minIndex;
    int min_bt = INT_MAX;
    int shortest = -1;
    int is_completed[n];
    for (int i = 0; i < n;i++){
        is_completed[i] = 0;
        p[i].remaining_bt = p[i].bt;
    }
    while(complete!=n){
        for (int j = 0; j < n; j++){
            if((p[j].at<=currentTime) && (p[j].remaining_bt<min_bt) && (p[j].remaining_bt>0) ){
                min_bt = p[j].remaining_bt;
                shortest = j;
            }
        }
        if(shortest==-1){
            currentTime++;
            continue;
        }
        p[shortest].remaining_bt--;
        min_bt = p[shortest].remaining_bt;
        if(min_bt==0){
            min_bt = INT_MAX;
        }
        if(p[shortest].remaining_bt==0){
            complete++;
            p[shortest].ct = currentTime + 1;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            if(p[shortest].wt<0)
                p[shortest].wt = 0;
            is_completed[shortest] = 1;
        }
        currentTime++;
    }
}

void display(struct Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
}

int main(){
        int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    printf("Enter Process ID, Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    printf("Choose Scheduling Algorithm:\n1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(p, n);
            printf("\nFCFS Scheduling Result:");
            display(p, n);
            break;
        case 2:
            SJF(p, n);
            printf("\nSJF Scheduling Result:");
            display(p, n);
            break;
        case 3:
            SJF_Preemptive(p, n);
            printf("\nPreemptive SJF Scheduling Result:");
            display(p, n);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}
