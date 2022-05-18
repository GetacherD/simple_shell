#include "main.h"
/**
* _strcpy_index - copy chars from src to dest starting from start_index
* @src: source string
* @dest: destination string
* @start_index: index of dest where copy starts
*/
void _strcpy_index(char *src, char *dest, size_t start_index)
{
	size_t j = 0;

	while (src[j])
	{
		dest[start_index + j] = src[j];
		j++;
	}
}
/**
 * readline -read line input
 * @status: read status
 * @len: number of chars read
 * Return: string or input
 */
char *readline(int  *status, ssize_t *len)
{
	ssize_t size = 5, n, i = 0;
	char *line = NULL, *cp;
	char c;

	line = malloc(sizeof(char) * size);
	_memset(line, size);
	if (line == NULL)
		return (NULL);
	n = read(STDIN_FILENO, &c, 1);
	if (n == 0)
	{
		*status = -1;
		free(line);
		return (NULL);
	}
	while (c != '\n')
	{
		if (i >= size)
		{
			size = size  * 2;
			cp = line;
			line = malloc(sizeof(char) * size);
			if (line == NULL)
			{
				*status = -1;
				return (cp);
			}
			_memset(line, size);
			_strcpy(cp, line);
			free(cp);
		}
		line[i++] = c;
		(*len)++;
		if ((read(STDOUT_FILENO, &c, 1) == 0) && (read(STDIN_FILENO, &c, 1) == 0))
		{
			*status = 2;
			break;
		}
	}
	return (line);
}
