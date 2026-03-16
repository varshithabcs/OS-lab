 #include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq, time = 0, completed = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d details:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
        p[i].ct = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100], front = 0, rear = 0;
    int inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && inQueue[i] == 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int idx = queue[front++];
        if (p[idx].rt > tq) {
            time += tq;
            p[idx].rt -= tq;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].rt > 0 && inQueue[i] == 0) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            queue[rear++] = idx;
        } else {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            completed++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].rt > 0 && inQueue[i] == 0) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
