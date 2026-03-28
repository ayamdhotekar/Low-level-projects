#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 64

void parse_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " \n");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        args[i] = strtok(NULL, " \n");
    }
}

int main() {
    char *line = NULL;
    size_t len = 0;
    char *args[MAX_ARGS];

    while (1) {
        printf("myshell> ");
        getline(&line, &len, stdin);

        if (strcmp(line, "\n") == 0) continue;

        parse_input(line, args);

        if (strcmp(args[0], "exit") == 0) break;

        if (strcmp(args[0], "cd") == 0) {
            if (args[1]) chdir(args[1]);
            continue;
        }

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }

    free(line);
    return 0;
}
