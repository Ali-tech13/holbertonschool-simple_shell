#include "shell.h"

/**
 * main - runs the simple shell loop
 * @argc: number of arguments
 * @argv: arguments passed to the program
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line;
	char *token;
	char **args;
	size_t size;
	size_t index;
	ssize_t chars_read;

	(void)argc;
	line = NULL;
	size = 0;

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

		args = malloc(sizeof(*args) * (chars_read + 1));
		if (args == NULL)
		{
			perror("malloc");
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
			execute_command(args, argv[0]);

		free(args);
	}

	free(line);
	return (0);
}
