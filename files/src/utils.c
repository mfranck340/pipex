/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:08:54 by ffierro-          #+#    #+#             */
/*   Updated: 2024/12/29 20:08:55 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	read_files(char *file1, char *file2, int *in_file, int *out_file)
{
	*in_file = open(file1, O_RDONLY);
	if (*in_file == -1)
	{
		perror(MSG_ERR_IN);
		return (0);
	}
	*out_file = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_file == -1)
	{
		close(*in_file);
		perror(MSG_ERR_OUT);
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
	if (!read_files(argv[1], argv[argc - 1], &(*pipex)->in_file,
			&(*pipex)->out_file))
	{
		free(*pipex);
		return (0);
	}
	(*pipex)->argv = argv;
	(*pipex)->envp = envp;
	(*pipex)->n_cmds = argc - 3;
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
		{
			last_status = WEXITSTATUS(*status);
		}
		i++;
	}
	*status = last_status;
	free_memory(pipex);
	return (1);
}
