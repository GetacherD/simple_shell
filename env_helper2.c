#include "main.h"
/**
* _unsetenv - unset environmenta var
* @name: env var to delete
* Return: 2 if success else -1
*/
int _unsetenv(const char *name,int *env_last_state, int *ind)
{
	size_t j = 0, index = 0;
	size_t removed_index = 0;
	char **new_env;
	while (environ[index])
		index++;
	new_env = malloc(sizeof(char *) * index);
	if (new_env == NULL)
		return (-1);
	removed_index = _getindex(name);
	for (j = 0; j < index; j++)
	{
		if (j >= removed_index)
		{
			new_env[j] = malloc(sizeof(char) * _strlen(environ[j + 1]));
			_strcpy(environ[j], new_env[j + 1]);
		}
		else
		{
			new_env[j] = malloc(sizeof(char) * _strlen(environ[j]));
			_strcpy(environ[j], new_env[j]);
		}
		j++;
	}
	j = 0;
	if (*env_last_state == 1)
	{
		while(ind[j] != -1)
		{
			free(environ[ind[j]]);
			j++;
		}
	}
	else if (*env_last_state == 2)
	{
		index = 0;
		while (environ[index])
		{
			free(environ[index]);
			ind[j] = -1;
			index++;
		}
		free(environ);
	}
	environ = new_env;
	*env_last_state = 2;
	return (0);
}

/**
* free_null_env - free memory if fail during allocation
* @newenv: new environmental var pointer
* @i: failed index
* Return: -1 always
*/
int free_null_env(char **newenv, ssize_t i)
{
	i--;
	while (i >= 0)
	{
		free(newenv[i]);
		i--;
	}
	free(newenv);
	return (0);
}
/**
* free_env - free environment variable after setenv call
* @en: environ var
* @status: return value of setenv call
* @index: new index of env var set by setenv call
*/
void free_env(char **en, int status, int index)
{
	size_t set = 0;

	if (status == 0)
		free(en[index]);
	else if (status == 1)
	{
		while (en[set])
		{
			free(en[set]);
			set++;
		}
		free(en);
	}
}
