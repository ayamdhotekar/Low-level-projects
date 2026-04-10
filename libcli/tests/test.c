#include <stdio.h>
#include <stdlib.h>
#include "../include/cli.h"

void hello(int argc, char **argv) {
    printf("Hello CLI!\n");
}

void add(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: add a b\n");
        return;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d\n", a + b);
}

int main() {
    cli_register("hello", hello);
    cli_register("add", add);

    cli_run();
    return 0;
}
