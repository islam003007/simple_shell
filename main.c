#include "main.h"

int search_command(char *args[], char **env)
{
	char *temp = NULL, *token = NULL, *path = _getenv("PATH", env);
	struct stat st;

	token = strtok(path, ":");
	temp = str_concat(token, args[0]);
	while (stat(temp, &st) != 0)
	{
		free(temp);
		token = strtok(NULL, ":");
		if (token == NULL)
		{
			free(path);
			return (0);
		}
		temp = str_concat(token, args[0]);
	}

	args[0] = temp;
	free(path);
	return (1);
}

/**
 * excute - excutes command.
 *
 * @args: inputs arguments.
 * @env: inputs env.
 * @argv: inputs argv.
 *
 * Return: 0 on success, -1 on failure.
*/

int excute(char *args[], char **env, char **argv)
{
	pid_t child;
	int status;
	struct stat st;

	child = fork();
	if (child != 0)
		wait(&status);
	else
	{
		if (stat(args[0], &st) == 0)
			execve(args[0], args, env);
		else
			printf("%s: No such file or directory\n", argv[0]);
		return (-1);
	}

	return (0);
}


/**
 * parser - parses the input
 *
 * @args: inputs args array.
 * @buf: inputs buffer of input.
*/

void parser(char *args[], char *buf)
{
	int i;
	char *token;

	i = 0;
	token = strtok(buf, " \t\n");
	while (token != NULL && i < MAX_ARG - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL;
}

/**
 * interface - interface for the shell.
 *
 * @buf: inputs buffer.
 *
 * Return: returns characters read on success, -1 of fail or eof.
*/

ssize_t interface(char **buf)
{
	ssize_t temp = 0;
	size_t n = 0;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);

	temp = getline(buf, &n, stdin);

	if (_strncmp(*buf, "exit", 4) == 0)
		return (-1);

	if (_strncmp(*buf, "env", 3) == 0)
		return (-2);

	return (temp);
}

/**
 * main - entry point
 *
 * @argc: argc.
 * @argv: argv.
 * @env: env.
 *
 * Return: 0
*/

int main(int argc, char **argv, char **env)
{
	char *buf = NULL;
	char *args[MAX_ARG];
	int temp;

	while (1)
	{
		temp = interface(&buf);

		if (temp == -1)
		{
			free(buf);
			break;
		}
		if (temp == -2)
		{
			print_env(env);
			free(buf);
			continue;
		}
		parser(args, buf);

		excute(args, env, argv);

		free(buf);
	}

	(void)argc;
	return (0);
}
