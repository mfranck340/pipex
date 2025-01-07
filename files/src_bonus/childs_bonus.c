/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:09:14 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/06 22:43:33 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (0);
}

static char	*get_path_command(char *command, char **paths)
{
	int		i;
	char	*path_aux;

	if (access(command, F_OK) == 0)
		return (command);
	i = 0;
	while (paths[i] != 0)
	{
		path_aux = ft_strjoin(paths[i], "/");
		if (path_aux == 0)
		{
			perror(MSG_ERR_JOIN);
			return (0);
		}
		path_aux = ft_strjoin(path_aux, command);
		if (path_aux == 0)
		{
			perror(MSG_ERR_JOIN);
			return (0);
		}
		if (access(path_aux, F_OK) == 0)
			return (path_aux);
		i++;
	}
	return (0);
}

static char	*search_path(char *command, char **envp)
{
	char	**paths;
	char	*path_aux;

	path_aux = get_paths(envp);
	paths = ft_split(path_aux, ':');
	if (paths == 0)
	{
		perror(MSG_ERR_SPLIT);
		return (0);
	}
	path_aux = get_path_command(command, paths);
	if (path_aux == 0)
	{
		perror(MSG_ERR_JOIN);
		return (0);
	}
	return (path_aux);
}

static int	execute_command(char *command, char **envp)
{
	char	**args;
	char	*path;
	int		i;

	args = ft_split(command, ' ');
	if (args == NULL)
	{
		perror(MSG_ERR_SPLIT);
		return (1);
	}
	path = search_path(args[0], envp);
	if (path == NULL)
	{
		perror(MSG_ERR_JOIN);
		return (1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		execve(path, args, envp);
		i++;
	}
	perror(MSG_ERR_EXEC);
	return (1);
}

int	child_process(t_pipex *pipex, int i)
{
	int	n_cmd;

	if (i == 0)
	{
		dup2(pipex->in_file, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
	}
	else if (i == pipex->n_cmds - 1)
	{
		dup2(pipex->pipefd[2 * i - 2], STDIN_FILENO);
		dup2(pipex->out_file, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipefd[2 * i - 2], STDIN_FILENO);
		dup2(pipex->pipefd[2 * i + 1], STDOUT_FILENO);
	}
	close_pipes(pipex);
	if (pipex->in_file == 0)
		n_cmd = i + 3;
	else
		n_cmd = i + 2;
	execute_command(pipex->argv[n_cmd], pipex->envp);
	return (1);
}
