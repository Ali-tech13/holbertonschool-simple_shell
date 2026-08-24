#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

ssize_t read_command(char **line, size_t *size);
void execute_command(char *command, char *program_name);

#endif
