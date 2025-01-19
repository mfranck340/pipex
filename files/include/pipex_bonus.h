/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:47:44 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/19 23:47:45 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define BUFFER_SIZE 8

void	execute(char *argv, char **envp, int *fd);
void	exit_error(char *msg);
char	**parse_command(char *command);
int		get_input_file(char *limiter);
char	*get_next_line(int fd);
void	child_process(int argc, char **argv, int *fd, int i);
int		get_number_of_commands(char **argv, int argc);
int		get_number_of_pipes(int argc, char **argv);
void	close_pipes(int *fd, int num_pipes);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif
