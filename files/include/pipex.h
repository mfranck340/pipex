/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:33:23 by ffierro-          #+#    #+#             */
/*   Updated: 2024/12/29 16:33:24 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define MSG_ERR_PIPE "Error creating pipe"
# define MSG_ERR_CHILD "Error creating child process"
# define MSG_ERR_EXEC "Error executing command"
# define MSG_ERR_IN "Error opening input file"
# define MSG_ERR_OUT "Error opening output file"
# define MSG_ERR_JOIN "Error joining path"
# define MSG_ERR_SPLIT "Error splitting path"
# define MSG_ERR_ALLOC "Error allocating memory"

typedef struct s_pipex
{
	int		in_file;
	int		out_file;
	char	**argv;
	char	**envp;
	int		n_cmds;
	int		*pipefd;
}	t_pipex;

int		child_process(t_pipex *pipex, int i);
int		init_pipex(t_pipex **pipex, int argc, char **argv, char **envp);
void	close_pipes(t_pipex *pipex);
int		close_and_wait(t_pipex *pipex, int *status);
void	free_memory(t_pipex *pipex);

#endif
