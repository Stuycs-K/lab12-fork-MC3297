#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t parent = getpid();
    printf("%d about to create 2 child processes.\n", parent);
    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            pid_t child = getpid();
            srand(time(NULL)^child);
            int n = rand()%5+1;
            printf("%d %dsec\n", child, n);
            sleep(n);
            printf("%d finished after %d sec\n", child, n);
            exit(n);//tells parent what sleep time was
        }
        else if (pid < 0) {
            perror("fork fail");
            exit(1);
        }
    }

    int status;
    pid_t done = wait(&status);
    printf("Main Process %d is done. Child %d slept for %dsec\n", parent, done, WEXITSTATUS(status));

    return 0;
}
