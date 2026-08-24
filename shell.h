#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

ssize_t read_command(char **line, size_t *size);
void execute_command(char **args, char *program_name);

#endif
