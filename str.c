#include "main.h"

/**
 * _strcat - concatenates two strings
 *
 * @dest: provides destination
 * @src: provides source
 *
 * Return: a pointer to destination
*/

char *_strcat(char *dest, char *src)
{
	int dest_index = 0;
	int src_index = 0;

	while (dest[dest_index])
		dest_index++;
	while (src[src_index])
	{
		dest[dest_index] = src[src_index];
		src_index++;
		dest_index++;
	}
	dest[dest_index] = src[src_index];
	return (dest);
}

/**
 * _strlen - strlen
 *
 * @str: inputs string.
 *
 * Return: string length.
*/

unsigned int _strlen(char *str)
{
	unsigned int i;

	if (str == NULL || str[0] == '\0')
		return (0);

	for (i = 0; str[i]; i++)
		;

	return (i);
}

/**
 * _strncmp - compares between two strings.
 *
 * @s1: provides first input.
 * @s2: provides second input.
 * @n: max number of comparisons
 *
 * Return: an integer less than, equal to, or greater than zero if s1 is found
 * , respectively, to be less than, to match, or be greater than s2.
*/
int _strncmp(char *s1, char *s2, int n)
{
	int result = 0;
	int i = 0;

	while (s1[i] && i < n)
	{
		result = s1[i] - s2[i];
		if (s1[i] != s2[i])
			break;
		i++;
	}
	return (result);
}

/**
 * _realloc - realloc.
 *
 * @ptr: pointer to perviously allocated memory.
 * @old_size: size of perviously allocated memory.
 * @new_size: new size to reallocate.
 *
 * Return: void pointer the reallocated memory.
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(sizeof(char) * new_size);

	if (ptr == NULL)
		return (new_ptr);

	if (new_ptr == NULL)
		return (NULL);

	if (old_size < new_size)
		new_size = old_size;

	for (i = 0; i < new_size; i++)
		*((char *)new_ptr + i) = *((char *)ptr + i);

	free(ptr);

	return (new_ptr);
}

/**
 * str_concat - uses malloc then concatenates 2 strings and puts / between.
 * WARNING:memory must be freed.
 *
 * @s1: inputs string.
 * @s2: inputs string.
 *
 * Return: pointer to concatenated string.
*/

char *str_concat(char *s1, char *s2)
{
	int s1_len = 0;
	int s2_len = 0;
	int counter;
	char *str;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	s1_len = _strlen(s1);

	s2_len = _strlen(s2);

	str = malloc(sizeof(char) * (s1_len + s2_len + 2));

	if (str == NULL)
		return (NULL);

	for (counter = 0; counter < s1_len; counter++)
		str[counter] = s1[counter];

	str[s1_len] = '/';

	for (counter = 0; counter <= s2_len; counter++)
		str[counter + s1_len + 1] = s2[counter];

	return (str);

}
