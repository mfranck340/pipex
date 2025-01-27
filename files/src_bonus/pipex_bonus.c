/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:35:54 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/21 14:09:31 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	parent_wait(int *status, int num_comands)
{
	int		i;

	i = -1;
	while (++i < num_comands)
	{
		wait(status);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
}

static void	create_childs(int argc, char **argv, char **envp, int *fd)
{
	pid_t	pid;
	int		i;
	int		num_cmds;

	i = -1;
	num_cmds = get_number_of_commands(argv, argc);
	while (++i < num_cmds)
	{
		pid = fork();
		if (pid == -1)
			exit_error("fork");
		if (pid == 0)
		{
			child_process(argc, argv, fd, i);
			if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
				execute(argv[i + 3], envp, fd);
			else
				execute(argv[i + 2], envp, fd);
		}
	}
}

static void	init_pipes(int **fd, int argc, char **argv)
{
	int	num_pipes;
	int	i;

	num_pipes = get_number_of_pipes(argc, argv);
	*fd = (int *)malloc(sizeof(int) * num_pipes * 2);
	if (!*fd)
		exit_error("malloc");
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(*fd + (i * 2)) == -1)
			exit_error("pipe");
		i ++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		*fd;
	int		status;

	status = 0;
	if (argc >= 5)
	{
		init_pipes(&fd, argc, argv);
		create_childs(argc, argv, envp, fd);
		close_pipes(fd, get_number_of_pipes(argc, argv));
		parent_wait(&status, get_number_of_commands(argv, argc));
		if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
			unlink(".here_doc");
		free(fd);
	}
	else
	{
		ft_printf("Usage:\t./pipex <file1> <cmd1> ... <cmd2> <file2>\n");
		ft_printf("\t./pipex here_doc <limiter> <cmd1> ... <cmd2> <file2>\n");
		return (2);
	}
	return (status);
}
