#include "shell.h"

/**
 * print_env - prints the current environment
 *
 * Return: nothing
 */
static void print_env(void)
{
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * check_builtin - checks if a command is a builtin and executes it
 * @args: command and its arguments
 * @should_exit: set to 1 if the exit builtin was called
 *
 * Return: 1 if args[0] was a builtin, 0 otherwise
 */
int check_builtin(char **args, int *should_exit)
{
	if (strcmp(args[0], "exit") == 0)
	{
		*should_exit = 1;
		return (1);
	}

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}
