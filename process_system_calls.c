#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = getpid();
    printf("Before fork: Process ID = %d\n", pid);

    pid = fork();

    if (pid < 0)
    {
        printf("\nFork failed\n");
        exit(1);
    }

    else if (pid == 0)
    {
        printf("\nThis line is from child.\nThe child process ID is %d\n", getpid());

        execl("/bin/ls", "ls", "-l", (char *)0);

        printf("execl failed\n");
        exit(1);
    }

    else
    {
        printf("\nThis line is from parent.\nThe parent process ID is %d\n", getpid());
        wait(NULL);
    }

    return 0;
}
