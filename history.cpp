#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_LINE 80

using namespace std;

int main(void)
{
    char *args[MAX_LINE / 2 + 1];
    int should_run = 1;
    printf("Write \'quit\' to exit.\n");

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

        char text[50];
        fgets(text, 50, stdin);

        char *pieces = strtok(text, " ");
        int i = 0;
        while (pieces != NULL) //convert one line text to words
        {
            char *newLine = strchr(pieces, '\n');
            if (newLine)
            {
                *newLine = 0;
                args[i] = pieces;
                break;
            }

            args[i] = pieces;

            pieces = strtok(NULL, " ");
            i++;
        }
        args[i + 1] = NULL;

        if (strcmp(args[0], "quit") == 0) //quit program
        {
            should_run = 0;
            continue;
        }

        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            printf("Not able to create child process");
            printf("\n");
        }
        else if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                printf("Error command not found");
            }
            printf("\n");
        }
        else
        {
            wait(NULL);
        }
    }
}