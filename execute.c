#include "shell.h"

/**
 * execute_command - finds and executes a command
 * @args: command and its arguments
 * @program_name: name used when printing errors
 * @command_number: number of the command being executed
 *
 * Return: exit status of the command
 */
int execute_command(char **args, char *program_name,
		unsigned int command_number)
{
	pid_t pid;
	int status;
	char *command_path;

	command_path = find_command(args[0]);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
				program_name, command_number, args[0]);
		return (127);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(command_path, args, environ);
		perror(program_name);
		free(command_path);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		free(command_path);
		return (1);
	}

	free(command_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}