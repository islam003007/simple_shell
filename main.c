#include "main.h"

/**
 * search_command - searches for command.
 *
 * @args: inputs args.
 * @env: inputs env.
 *
 * Return: 0 if found, -1 if not found
*/

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
			return (-1);
		}
		temp = str_concat(token, args[0]);
	}

	args[0] = temp;
	free(path);
	return (0);
}

/**
 * excute - excutes command.
 *
 * @args: inputs arguments.
 * @env: inputs env.
 * @argv: inputs argv.
 * @line: inputs line ptr.
 *
 * Return: 0 on success, -1 on failure.
*/

void excute(char *args[], char **env, char **argv, int *line)
{
	pid_t child;
	int status, temp, flag = 0;
	struct stat st;

	temp = stat(args[0], &st);
	if (temp != 0)
	{
		temp = search_command(args, env);
		flag = 1;
	}
	if (temp != 0)
	{
		printf("%s: %i: fsd: not found\n", argv[0], *line);
		return;
	}
	else
	{
		child = fork();
		if (child != 0)
		{
			wait(&status);
			if (flag)
				free(args[0]);
			return;
		}
		execve(args[0], args, env);
	}
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
 * @line: inputs line ptr.
 *
 * Return: returns characters read on success, -1 of fail or eof.
*/

ssize_t interface(char **buf, int *line)
{
	ssize_t temp = 0;
	size_t n = 0;

	(*line)++;
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
	int line = 0;

	signal(SIGINT, void (*)(int,  char *)NThandler);
	while (1)
	{
		temp = interface(&buf, &line);

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

		excute(args, env, argv, &line);

		free(buf);
	}

	(void)argc;
	return (0);
}
