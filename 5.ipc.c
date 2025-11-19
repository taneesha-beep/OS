#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int FileDes[2];
    pid_t pid;
    char write_msg[100];
    char read_msg[100];

    if (pipe(FileDes) == -1)
    {
        printf("Pipe creation failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid > 0)
    {

        close(FileDes[0]);

        printf("Parent: Enter a message to send to child: ");
        scanf("%[^\n]", write_msg);

        write(FileDes[1], write_msg, strlen(write_msg) + 1);

        close(FileDes[1]);

        wait(NULL);
        printf("Parent: Child process completed. Exiting.\n");
    }
    else
    {

        close(FileDes[1]);

        read(FileDes[0], read_msg, sizeof(read_msg));

        printf("Child: Received message: %s\n", read_msg);

        close(FileDes[0]);
    }

    return 0;
}