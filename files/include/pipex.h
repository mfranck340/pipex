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
# define MSG_ERR_CHILD "fork"
# define MSG_ERR_EXEC "Error executing command"
# define MSG_ERR_JOIN "join"
# define MSG_ERR_SPLIT "split"
# define MSG_ERR_ALLOC "malloc"

void	execute(char *argv, char **envp);
void	exit_error(char *msg);
char	**parse_command(char *command);

#endif
