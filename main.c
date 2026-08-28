#include "shell.h"

/**
 * main - runs the simple shell loop
 * @argc: number of arguments
 * @argv: arguments passed to the program
 *
 * Return: status of the last executed command
 */
int main(int argc, char **argv)
{
	char *line;
	char *token;
	char **args;
	size_t size;
	size_t index;
	ssize_t chars_read;
	unsigned int command_number;
	int status;
	int should_exit;

	(void)argc;
	line = NULL;
	size = 0;
	command_number = 0;
	status = 0;
	should_exit = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("($) ");
			fflush(stdout);
		}

		chars_read = read_command(&line, &size);

		if (chars_read == -1)
		{
			if (isatty(STDIN_FILENO))
				putchar('\n');

			break;
		}

		command_number++;

		args = malloc(sizeof(*args) * (chars_read + 1));

		if (args == NULL)
		{
			perror("malloc");
			status = 1;
			break;
		}

		index = 0;
		token = strtok(line, " \t\n");

		while (token != NULL)
		{
			args[index] = token;
			index++;
			token = strtok(NULL, " \t\n");
		}

		args[index] = NULL;

		if (args[0] != NULL)
		{
			if (check_builtin(args, &should_exit))
				status = 0;
			else
				status = execute_command(args, argv[0], command_number);
		}

		free(args);

		if (should_exit)
			break;
	}

	free(line);

	return (status);
}