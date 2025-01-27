/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:36:03 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/21 14:08:54 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	exit_error(char *msg)
{
	perror(msg);
	exit(1);
}

static void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_array(paths);
	return (0);
}

void	execute(char *argv, char **envp, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = parse_command(argv);
	if (!cmd)
		exit_error("parse command");
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_array(cmd);
		free(fd);
		exit_error("Command not found");
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_array(cmd);
		free(path);
		free(fd);
		exit_error("execve");
	}
}
