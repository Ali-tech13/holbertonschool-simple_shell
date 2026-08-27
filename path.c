#include "shell.h"

/**
 * build_path - joins a directory with a command name
 * @directory: beginning of a directory in PATH
 * @length: number of characters in the directory
 * @command: command name
 *
 * Return: allocated full path, or NULL on failure
 */
static char *build_path(char *directory, size_t length, char *command)
{
	char *full_path;
	size_t command_length;

	command_length = strlen(command);

	if (length == 0)
	{
		directory = ".";
		length = 1;
	}

	full_path = malloc(length + command_length + 2);
	if (full_path == NULL)
		return (NULL);

	memcpy(full_path, directory, length);
	full_path[length] = '/';
	memcpy(full_path + length + 1, command, command_length + 1);

	return (full_path);
}

/**
 * find_command - finds an executable command using PATH
 * @command: command name or path
 *
 * Return: allocated executable path, or NULL if not found
 */
char *find_command(char *command)
{
	char *path;
	char *start;
	char *end;
	char *full_path;
	size_t length;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));

		return (NULL);
	}

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	start = path;

	while (1)
	{
		end = strchr(start, ':');

		if (end == NULL)
			length = strlen(start);
		else
			length = end - start;

		full_path = build_path(start, length, command);

		if (full_path == NULL || access(full_path, X_OK) == 0)
			return (full_path);

		free(full_path);

		if (end == NULL)
			break;

		start = end + 1;
	}

	return (NULL);
}