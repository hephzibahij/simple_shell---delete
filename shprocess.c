#include "shell.h"

/**
 * child - A function that creates a sub process.
 *@cmd: The pointer to tokenized cmd
 *@progname: The pointer to the progname of shell.
 *@env: The pointer to the enviromental variables.
 *@f: Number of executed f.
 */
void child(char **cmd, char *progname, char **env, int f)
{
	int pid = 0;
	int status = 0;
	int wait_error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_exit(cmd);
	}
	else if (pid == 0)
	{
		execute(cmd, progname, env, f);
		free_rp(cmd);
	}
	else
	{
		wait_error = waitpid(pid, &status, 0);
		if (wait_error < 0)
		{
			free_exit(cmd);
		}
		free_rp(cmd);
	}
}

/**
 * change_dir - Afunction that changes working directory.
 *@path: The new current working directory.
 * Return: 0 on success, -1 on failure.
 */
int change_dir(const char *path)
{
	char *buf = NULL;

	size_t size = 1024;

	if (path == NULL)
		path = getcwd(buf, size);
	if (chdir(path) == -1)
	{
		perror(path);
		return (98);
	}
	return (1);
}
