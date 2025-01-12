

#include "../include/pipex.h"
#include <stdio.h>


void	add_index(int *i, int *count, char *command, char limit)
{
	(*count)++;
	while (command[*i] != '\0' && command[*i] != limit)
		(*i)++;
}

int	count_args(char *command)
{
	int i;
	int count;
	char limit;

	i = 0;
	count = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			limit = command[i++];
			add_index(&i, &count, command, limit);
			if (command[i] != '\0')
				i++;
		}
		else if (command[i] != ' ' )
			add_index(&i, &count, command, ' ');
		else
			i++;
	}
	return (count);
}

int	read_words()
{
	int i;
	int j;
	int count;
	char limit;

	i = 0;
	j = 0;
	while (command[i] != '\0')
	{
		count = 0;
		if (command[i] == '\'' || command[i] == '\"')
		{
			limit = command[i];
			count++;
			while (command[i + count] != '\0' && command[i + count] != limit)
				count++;
			count++;
			args[j] = ft_substr(command, i, count);
			j++;
			i+=count;
		}
		else if (command[i] != ' ')
		{
			count++;
			while (command[i + count] != '\0' && command[i + count] != ' ')
				count++;
			args[j] = ft_substr(command, i, count);
			j++;
			i += count;
		}
		else
			i++;
	}
	return (1);
}

char	**parse_command(char *command)
{
	int i;
	int count;
	char limit;
	char **args;

	count = count_args(command);
	ft_printf("PALABRAS CONTADAS: %d\n", count);
	args = malloc(sizeof(char *) * (count + 1));
	if (args == 0)
	{
		perror("Error allocating memory");
		return (0);
	}
	args[count] = 0;
	if (!read_words())
	{
		free(args);
		return (0);
	}
	return (args);
}

int main(int argc, char **argv)
{
	int i;

	//char *command = "grep -r -i --include=\"*.log\" \"error\" \"/path/to/logs\" --exclude=\"*.bak\"";
	//char *command = "ls -l -a -h /home/user/";
	//char *command = "./prog\\ one";
	//char *command = "awk '{print "Texto: \"" $0 "\""}'";

	char **args;
	char *command = argv[1];

	i = 0;
	args = parse_command(command);
	while (args[i] != 0)
	{
		ft_printf("ARGUMENTO %d: %s\n", i, args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}
