#include "main.h"
/**
* get_absolute_path -get absolute path give file name
* @name: file name to be searched
* Return: on success absolute path on fail  NULL
*/
char *get_absolute_path(char *name)
{
	char *path_cwd, *path_in_path;

	if (name[0]  == '/')
	{
		return (name);
	}
	path_cwd = check_in_cwd(name);
	if (path_cwd)
		return (path_cwd);
	path_in_path = check_in_path(name);
	if (path_in_path)
		return (path_in_path);
	return (NULL);
}
/**
 * print_env - print environmental variables
 * @env: env var array
 */
void print_env(char **env)
{
	size_t i = 0;

	while (env[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
/**
* call_setenv - function that set env var
* @argv: total arg vector
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* Return: 1 always
*/


int call_setenv(char **argv, int *exit_status,
	int *env_last_state, int *index, int *cur_state,
	int *cur_index, int *add_case, size_t *count)
{
	if (argv[1] && argv[2])
		_setenv(argv[1], argv[2], 1, env_last_state,
			index, cur_state, cur_index, add_case);
	else
	{
		dprintf(STDERR_FILENO, "usage: setenv var value\n");
		*exit_status = 0;
		(*count)++;
	}
	*exit_status = 0;
	return (1);
}
/**
 * echo - variable sbstitution function
 * @argv: command line args
 * @exit_status: set exit status
 * @count: set command count
 * Return: 1 always
 */
int echo(char **argv, int *exit_status, size_t *count)
{
	if ((_strcmp(argv[1], "$$") == 0))
	{
		printf("%u\n", getppid());
		*exit_status = 0;
		(*count)++;
		return (1);
	}
	if (_strcmp(argv[1], "$?") == 0)
	{
		printf("%d\n", *exit_status);
		*exit_status = 0;
		(*count)++;
		return (1);
	}
	if (_getenv(&(argv[1][1])))
		printf("%s\n", _getenv(&(argv[1][1])));
	else
	{
		printf("No env var\n");
		*exit_status = 0;
		(*count)++;
	}
	return (1);
}


