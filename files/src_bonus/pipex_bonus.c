/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:33:12 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/06 22:43:49 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	create_pipes(int count, int *pipefd)
{
	int	i;

	i = 0;
	while (i < 2 * (count - 1))
	{
		if (pipe(pipefd + i) == -1)
		{
			perror(MSG_ERR_PIPE);
			return (0);
		}
		i += 2;
	}
	return (1);
}

int	spawn_child(t_pipex *pipex)
{
	int	pid;
	int	i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror(MSG_ERR_CHILD);
			return (0);
		}
		if (pid == 0)
		{
			return (child_process(pipex, i));
		}
		i++;
	}
	return (1);
}

void	free_memory(t_pipex *pipex)
{
	if (ft_strncmp(pipex->argv[1], "here_doc", 8) == 0)
		unlink(".here_doc");
	else
		close(pipex->in_file);
	close(pipex->out_file);
	free(pipex->pipefd);
	free(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;

	if (argc < 5)
	{
		ft_printf("Usage:\t./pipex <file1> <cmd1> ... <cmd2> <file2>\n");
		ft_printf("\t./pipex here_doc LIMITER <cmd1> ... <cmd2> <file2>\n");
		return (1);
	}
	if (!init_pipex(&pipex, argc, argv, envp))
		return (1);
	if (!create_pipes(pipex->n_cmds, pipex->pipefd))
	{
		free_memory(pipex);
		return (1);
	}
	if (!spawn_child(pipex))
	{
		free_memory(pipex);
		return (1);
	}
	if (!close_and_wait(pipex, &status))
		return (1);
	return (status);
}
