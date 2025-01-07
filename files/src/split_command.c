

#include "../include/pipex.h"
#include <stdio.h>

int	has_special_char(char *command)
{
	int	i;

	i = 0;
	while (command[i] != 0)
	{
		if (command[i] == ' ')
		{
			if (command[i + 1] == '\'' || command[i] == '\"')
				return (1);
		}
		i++;
	}
	return (0);
}

char	**parse_command(char *command)
{
	int i;
	int count;
	int len;

	len = ft_strlen(command);
	count = 0;
	i = -1;
	while (++i < len)
	{
		if ((command[i] == '\'' || command[i] == '\"')
				&& (0 == i || (i > 0 && command[i - 1] == ' ')))
		{
			ft_printf("case 1 - new arg: %d - %c\n", i, command[i]);
			count++;
			while (command[i] != 0 && !((command[i] == '\'' || command[i] == '\"') && (command[i + 1] == ' ' || command[i + 1] == 0)))
				i++;
		}
		else if (command[i] != ' ' )
		{
			ft_printf("case 2 - new arg: %d - %c\n", i, command[i]);
			count++;
			while (command[i] != 0 && command[i] != ' ')
				i++;
		}
	}
	ft_printf("count: %d\n", count);
	return (0);
}

/*
char	**get_args_command(char *command)
{
	char	**args;
	int		i;
	int		opt;

	opt = has_special_char(command);
	if (opt == 0)
		args = ft_split(command, ' ');
	else
		args = parse_command(command);
	if (args == 0)
	{
		perror("Error splitting command");
		return (0);
	}
	i = 0;
	while (args[i] != 0)
	{
		i++;
	}
	if (i == 0)
	{
		perror("Error getting command");
		return (0);
	}
	return (args);
}*/

int main(int argc, char **argv)
{
	int len;
	int i;

	//char *command = "grep -r -i --include=\"*.log\" \"error\" \"/path/to/logs\" --exclude=\"*.bak\"";
	//char *command = "ls -l -a -h /home/user/";
	//char *command = "./prog\\ one";
	//char *command = "awk '{print "Texto: \"" $0 "\""}'";

	char *command = argv[1];
	len = ft_strlen(command);
	i = 0;
	while (i < len)
	{
		printf("%c\n", command[i]);
		i++;
	}
	
	parse_command(command);
	return (0);
}
