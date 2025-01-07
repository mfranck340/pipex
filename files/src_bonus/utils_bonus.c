/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:08:54 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/06 22:43:59 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	read_files(char *file1, char *file2, t_pipex **pipex)
{
	if (!file1)
		(*pipex)->in_file = get_input_file((*pipex)->argv[2]);
	else
		(*pipex)->in_file = open(file1, O_RDONLY);
	if ((*pipex)->in_file < 0)
	{
		perror(MSG_ERR_IN);
		return (0);
	}
	if (!file1)
		(*pipex)->out_file = open(file2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		(*pipex)->out_file = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*pipex)->out_file < 0)
	{
		close((*pipex)->in_file);
		perror(MSG_ERR_OUT);
		return (0);
	}
	return (1);
}

int	load_files(t_pipex **pipex, int argc, char **argv)
{
	char	*input_file;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		(*pipex)->n_cmds = argc - 4;
		input_file = 0;
	}
	else
	{
		(*pipex)->n_cmds = argc - 3;
		input_file = argv[1];
	}
	if (!read_files(input_file, argv[argc - 1], &(*pipex)))
	{
		free(*pipex);
		return (0);
	}
	return (1);
}

int	init_pipex(t_pipex **pipex, int argc, char **argv, char **envp)
{
	*pipex = malloc(sizeof(t_pipex));
	if (*pipex == NULL)
	{
		perror(MSG_ERR_ALLOC);
		return (0);
	}
	(*pipex)->argv = argv;
	(*pipex)->envp = envp;
	if (!load_files(pipex, argc, argv))
		return (0);
	(*pipex)->pipefd = malloc(sizeof(int) * 2 * ((*pipex)->n_cmds - 1));
	if ((*pipex)->pipefd == 0)
	{
		close((*pipex)->in_file);
		close((*pipex)->out_file);
		free(*pipex);
		perror(MSG_ERR_ALLOC);
		return (0);
	}
	return (1);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 2 * (pipex->n_cmds - 1))
	{
		close(pipex->pipefd[i]);
		i++;
	}
}

int	close_and_wait(t_pipex *pipex, int *status)
{
	int	i;
	int	last_status;

	i = 0;
	last_status = 0;
	close_pipes(pipex);
	while (i < pipex->n_cmds)
	{
		wait(status);
		if (WIFEXITED(*status))
			last_status = WEXITSTATUS(*status);
		i++;
	}
	*status = last_status;
	free_memory(pipex);
	return (1);
}
