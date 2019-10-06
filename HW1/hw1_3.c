#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MAX_LINE 80

void print(int n) {
    int pid = getpid();
    int ppid = getppid();
    printf("Fork %d. I'm the child %d, my parent is %d.\n", n, pid, ppid);
}

int main(void)
{
    int pid = fork(); // fork 1

    if (pid > 0) {
        int status = -1;
        waitpid(pid, &status, 0);
        return 0;
    }

    print(1);

    int main_pid = getppid();
    for (int i = 0; i < 2; i ++) {
        if (getppid() == main_pid) {
            pid = fork(); // fork 2
            if (pid == 0)
                print(2);
        }
    }

    if (getppid() != main_pid) {
        pid = fork();
        if (pid == 0)
            print(3);
        else {
            int status = -1;
            waitpid(pid, &status, 0);
        }
    }
        

	return 0;
}

