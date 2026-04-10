#ifndef CLI_H
#define CLI_H

typedef void (*command_fn)(int argc, char **argv);

void cli_register(const char *name, command_fn fn);
void cli_run();

#endif
