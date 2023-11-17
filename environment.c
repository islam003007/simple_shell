#include "main.h"


/**
 * print_env - prints env.
 *
 * @env: inputs env
*/

void print_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}


/**
 * _getenv - get env, WARNING: memory returned must be freed after use.
 *
 * @name : inputs.
 * @env: env
 *
 * Return: pointer to initliazed enviroment.
*/


char *_getenv(char *name, char **env)
{
	int i = 0;
	unsigned int name_len = _strlen(name);
	unsigned int env_len;
	char *new_env, *temp;

	while (env[i] != NULL)
	{
		if (_strncmp(env[i], name, name_len) == 0)
			break;
		i++;
	}

	if (env[i] == NULL)
		return (NULL);

	temp = env[i];

	env_len = _strlen(temp);

	new_env = malloc(sizeof(char) * (env_len - name_len));

	if (new_env == NULL)
		return (NULL);

	i = 0;

	while (temp[i + name_len + 1])
	{
		new_env[i] = temp[i + name_len + 1];
		i++;
	}

	new_env[i] = '\0';

	return (new_env);
}

/**
 * exit_sh - exits shell.
 *
 * @args: inputs args.
 * @exit_st: inputs pointer to exit status.
 * @argv: inputs argv.
 * @line: inputs line.
 *
 * Return: -1 if it fails.
*/


int exit_sh(char *args[], int *exit_st, char *argv[], int line)
{
	int i = 0;
	char *error_message = "%s: %i: exit: Illegal number: %s\n";

	if (args[1] == NULL)
		return (0);

	while (args[1][i])
	{
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			fprintf(stderr, error_message, argv[0], line, args[1]);
			(*exit_st) = 2;
			return (-1);
		}
		i++;
	}

	*exit_st = _atoi(args[1]);
	return (0);
}
