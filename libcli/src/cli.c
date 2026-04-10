#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cli.h"

#define MAX_COMMANDS 32
#define MAX_ARGS 16

typedef struct {
    char name[32];
    command_fn fn;
} command_t;

static command_t commands[MAX_COMMANDS];
static int count = 0;

void cli_register(const char *name, command_fn fn) {
    strcpy(commands[count].name, name);
    commands[count].fn = fn;
    count++;
}

static void parse(char *line, int *argc, char **argv) {
    *argc = 0;
    argv[(*argc)++] = strtok(line, " \n");
    while ((*argc < MAX_ARGS) && (argv[*argc] = strtok(NULL, " \n"))) {
        (*argc)++;
    }
}

void cli_run() {
    char line[256];
    char *argv[MAX_ARGS];
    int argc;

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) break;

        parse(line, &argc, argv);
        if (argc == 0) continue;

        if (strcmp(argv[0], "exit") == 0) break;

        for (int i = 0; i < count; i++) {
            if (strcmp(commands[i].name, argv[0]) == 0) {
                commands[i].fn(argc, argv);
                goto next;
            }
        }

        printf("Unknown command\n");
    next:;
    }
}
