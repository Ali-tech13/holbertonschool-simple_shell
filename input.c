#include "shell.h"

/**
 * read_command - reads one command line from standard input
 * @line: address of the command buffer
 * @size: size of the command buffer
 *
 * Return: number of characters read, or -1 on EOF/error
 */
ssize_t read_command(char **line, size_t *size)
{
	ssize_t chars_read;

	chars_read = getline(line, size, stdin);

	if (chars_read > 0 && (*line)[chars_read - 1] == '\n')
		(*line)[chars_read - 1] = '\0';

	return (chars_read);
}
