#include "shell.h"

/**
 * read_file - Read Command From File
 * @filename: Filename
 * @argv: Program Name
 * Return: -1 or 0
 */

void read_file(char *filename, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int ctr = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &len, fp) != -1)
	{
		ctr++;
		treat_file(line, ctr, fp, argv);
	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}

/**
 * treat_file - parse check command fork wait execute in line of file
 * @line: line from a file
 * @counter: error counter
 * @fp: file descriptor
 * @argv: program name
 * Return: execute a line void
 */

void treat_file(char *line, int counter, FILE *fp, char **argv)
{
	char **cmd;
	int sta = 0;

	cmd = parse_cmd(line);

	if (_strncmp(cmd[0], "exit", 4) == 0)
	{
		exit_bul_for_file(cmd, line, fp);
	}
	else if (check_builtin(cmd) == 0)
	{
		sta = handle_builtin(cmd, sta);
		free(cmd);
	}
	else
	{
		sta = check_cmd(cmd, line, counter, argv);
		free(cmd);
	}
}

/**
 * exit_bul_for_file - exit shell case of file
 * @cmd: parsed command
 * @line: line from a file
 * @fd: file descriptor
 * Return: case of exit in a file line
 */

void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
	int stat, x = 0;

	if (cmd[1] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][x])
	{
		if (_isalpha(cmd[1][x++]) < 0)
		{
			perror("illegal number");
		}
	}
	stat = _atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(stat);
}

