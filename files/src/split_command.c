
#include "../include/pipex.h"

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

int	read_words(char *command, char ***args)
{
	int i;
	int j;
	int k;
	char limit;

	i = 0;
	j = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			limit = command[i++];
			k = 0;
			while (command[i + k] != '\0' && command[i + k] != limit)
				k++;			
			(*args)[j] = ft_substr(command, i, k);
			if ((*args)[j] == 0)
			{
				while (j >= 0)
					free((*args)[j--]);
				return (0);
			}
			i += k + 1;
			j++;
		}
		else if (command[i] != ' ')
		{
			k = 0;
			while (command[i + k] != '\0' && command[i + k] != ' ')
				k++;
			(*args)[j] = ft_substr(command, i, k);
			if ((*args)[j] == 0)
			{
				while (j >= 0)
					free((*args)[j--]);
				return (0);
			}
			i += k;
			j++;
		}
		else
			i++;
	}
	return (1);
}

char	**parse_command(char *command)
{
	int count;
	char **args;

	count = count_args(command);
	args = malloc(sizeof(char *) * (count + 1));
	if (args == 0)
		return (0);
	args[count] = 0;
	if (!read_words(command, &args))
		return (0);
	return (args);
}
