/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:40:36 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/19 23:40:38 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	open_infile(char **argv)
{
	int	file;

	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		file = get_input_file(argv[2]);
	else
		file = open(argv[1], O_RDONLY);
	if (file == -1)
		exit_error("open");
	return (file);
}

int	open_outfile(char **argv, int argc)
{
	int	file;

	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		exit_error("open");
	return (file);
}

void	child_process(int argc, char **argv, int *fd, int i)
{
	int	file;

	if (i == 0)
	{
		file = open_infile(argv);
		dup2(file, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(file);
	}
	else if (i == get_number_of_commands(argv, argc) - 1)
	{
		file = open_outfile(argv, argc);
		dup2(fd[(i * 2) - 2], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
	{
		dup2(fd[(i * 2) - 2], STDIN_FILENO);
		dup2(fd[(i * 2) + 1], STDOUT_FILENO);
	}
	close_pipes(fd, get_number_of_pipes(argc, argv));
}
