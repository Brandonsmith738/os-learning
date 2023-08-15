#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int fd[2];
    int rc = fork();

    if (pipe(fd) < 0)
    {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    if (rc < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child (new process)
        write(fd[1], "hello world\n", strlen("hello world\n"));

        fork();
        if (rc == 0)
        {
            printf("hello, I am child (pid:%d)\n", (int)getpid());
            char inbuf[strlen("hello world\n") + 1];

            read(fd[0], inbuf, strlen("hello world\n"));
            printf("%s", inbuf);
        }

        else
        { // parent goes down this path (main)
            int rc_wait = waitpid(rc, NULL, WUNTRACED);
            printf("hello, I am parent of %d (pid:%d)\n",
                   rc, (int)getpid());
        }
    }

    return 0;
}
