 #include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int type;
    int ct;
    int tat;
    int wt;
    int start;
};

void sortByArrival(struct Process p[], int n) {
    int i, j;
    struct Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n, i, time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process sys[20], user[20];
    int ns = 0, nu = 0;

    for (i = 0; i < n; i++) {
        struct Process temp;
        printf("\nProcess %d details:\n", i + 1);
        printf("PID: ");
        scanf("%d", &temp.pid);
        printf("Arrival Time: ");
        scanf("%d", &temp.at);
        printf("Burst Time: ");
        scanf("%d", &temp.bt);
        printf("Type (0=System, 1=User): ");
        scanf("%d", &temp.type);

        if (temp.type == 0)
            sys[ns++] = temp;
        else
            user[nu++] = temp;
    }

    sortByArrival(sys, ns);
    sortByArrival(user, nu);

    for (i = 0; i < ns; i++) {
        if (time < sys[i].at)
            time = sys[i].at;
        sys[i].start = time;
        time += sys[i].bt;
        sys[i].ct = time;
        sys[i].tat = sys[i].ct - sys[i].at;
        sys[i].wt = sys[i].tat - sys[i].bt;
    }

    for (i = 0; i < nu; i++) {
        if (time < user[i].at)
            time = user[i].at;
        user[i].start = time;
        time += user[i].bt;
        user[i].ct = time;
        user[i].tat = user[i].ct - user[i].at;
        user[i].wt = user[i].tat - user[i].bt;
    }

    printf("\nPID\tAT\tBT\tType\tCT\tTAT\tWT\n");
    for (i = 0; i < ns; i++) {
        printf("%d\t%d\t%d\tSys\t%d\t%d\t%d\n",
               sys[i].pid, sys[i].at, sys[i].bt,
               sys[i].ct, sys[i].tat, sys[i].wt);
    }
    for (i = 0; i < nu; i++) {
        printf("%d\t%d\t%d\tUser\t%d\t%d\t%d\n",
               user[i].pid, user[i].at, user[i].bt,
               user[i].ct, user[i].tat, user[i].wt);
    }

    return 0;
}
