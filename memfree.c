#include "shell.h"

/**
 * free_rp - A function that frees all the memory allocated for cmd.
 *@cmd: The pointer to allocated memory to free.
 * Return: Nothing.
 */
void free_rp(char **cmd)
{
	size_t j = 0;

	if (cmd == NULL)
		return;
	while (cmd[j])
	{
		free(cmd[j]);
		j++;
	}
	if (cmd[j] == NULL)
		free(cmd[j]);
	free(cmd);
}
/**
 * free_exit - frees all the memory allocated and exit.
 *@cmd: allocated cmd memory to free.
 * Return: Nothing.
 */
void free_exit(char **cmd)
{
	size_t i = 0;

	if (cmd == NULL)
		return;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	if (cmd[i] == NULL)
		free(cmd[i]);
	free(cmd);
	exit(EXIT_FAILURE);
}
