#include "shell.h"
/**
 * execute_command - creates a child and executes a command
 * @command: full path of the command to execute
 * @program_name: name used when printing errors
 */
void execute_command(char *command, char *program_name)
{
	pid_t pid;
	char *args[2];

	args[0] = command
	args[1] = NULL;

	pid = fork();

	if (fork == -1)
	{
		perror("fork");
		return;
	}

	if (fork == 0)
	{
		execve(command,args,environ);
		perror(program_name);
		_exit(127);
	}

	waitpid(pid, NULL, 0);
}
