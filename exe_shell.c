#include "shell.h"

/**
 * execute - A function that executes a cmd.
 *@cmd: The pointer to tokienized cmd
 *@progname: The progname of the shell.
 *@env: The pointer to the enviromental variables.
 *@f: Number of executed f.
 * Return: Nothing.
 */
void execute(char **cmd, char *progname, char **env, int f)
{
	char **pathways = NULL, *full_path = NULL;
	struct stat st;
	unsigned int i = 0;

	if (_strcmp(cmd[0], "env") != 0)
		print_env(env);
	if (stat(cmd[0], &st) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			perror(progname);
			free_exit(cmd);
		}
	}
	else
	{
		pathways = get_path(env);
		while (pathways[i])
		{
			full_path = _strcat(pathways[i], cmd[0]);
			i++;
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, cmd, env) < 0)
				{
					perror(progname);
					free_rp(pathways);
					free_exit(cmd);
				}
				return;
			}
		}
		msgerror(progname, f, cmd);
		free_rp(pathways);
	}
}

/**
 * print_env - A function that prints all enviromental variables.
 *@env: The pointer to enviromental variables.
 *Return: Nothing.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;

	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
/**
 * msgerror - A function that prints message not found.
 *@progname: The progname of the shell.
 *@f: Number of f.
 *@cmd: The pointer to tokenized cmd.
 * Return: Nothing.
 */
void msgerror(char *progname, int f, char **cmd)
{
	char c;

	c = f + '0';
	write(STDOUT_FILENO, progname, _strlen(progname));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd[0], _strlen(cmd[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
