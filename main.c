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
	size_t size;
	ssize_t chars_read;
	char *command;

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
		command = strtok(line, " \t\n");

		if (command != NULL)
		execute_command(command, argv[0]);
	}

	free(line);
	return (0);
}
