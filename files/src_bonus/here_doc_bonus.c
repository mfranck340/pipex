/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:56:45 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/07 14:56:49 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	free_gnl(void)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		free(line);
		line = get_next_line(0);
	}
}

int	process_cmd_var(char *line, int fd)
{
	int	i;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '(')
			{
				free(line);
				line = ft_itoa(fd);
				if (!line)
					return (0);
			}
			else
			{
				i++;
				while (line[i] != '\0' && line[i] != ' ')
					i++;
			}
		}
		i++;
	}
	return (1);
}

int	get_input_file(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		{
			free(line);
			close(0);
			free_gnl();
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open(".here_doc", O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}
