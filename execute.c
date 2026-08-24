#include "shell.h"

/**
 * execute_command - creates a child and executes a command
 * @args: command and its arguments
 * @program_name: name used when printing errors
 */
void execute_command(char **args, char *program_name)
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror(program_name);
		_exit(127);
	}

	if (waitpid(pid, NULL, 0) == -1)
		perror("waitpid");
}
