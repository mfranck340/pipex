/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:40 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/21 14:09:52 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*update_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
	{
		free(str);
		return (0);
	}
	j = 0;
	while (str[++i])
		new_str[j++] = str[i];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

static char	*read_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = -1;
	while (str[++i] != '\n' && str[i])
		line[i] = str[i];
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*free_memory_gnl(char *str, char *buffer)
{
	if (str)
		free(str);
	if (buffer)
		free(buffer);
	return (0);
}

static char	*read_file(int fd, char *str)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_memory_gnl(str, 0));
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free_memory_gnl(str, buffer));
		buffer[bytes] = '\0';
		str = ft_strjoin_gnl(str, buffer);
		if (!str)
			return (free_memory_gnl(str, buffer));
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = read_file(fd, str);
	if (!str)
		return (0);
	line = read_line(str);
	if (!line)
	{
		free(str);
		str = 0;
		return (0);
	}
	str = update_str(str);
	return (line);
}
