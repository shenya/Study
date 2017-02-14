#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    pid_t pid = -1;
    int pipe_fd[2];
    int ret = -1;

    ret = pipe(pipe_fd);
    if (ret < 0)
    {
        printf("pipe failed\n");
        exit(1);
    }

    pid = fork();
    if (0 == pid)
    {
        printf("This is child process\n");
        close(pipe_fd[0]);
        write(pipe_fd[1], "hello", 5);
    }
    else if (pid > 0)
    {
        char buf[32];
        printf("This is parent process\n");
        close(pipe_fd[1]);
        read(pipe_fd[0], buf, sizeof(buf));
        printf("buf: %s\n", buf);
    }


    sleep(1);

    return 0;
}
