/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:40:49 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/19 23:40:51 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	get_number_of_commands(char **argv, int argc)
{
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		return (argc - 4);
	return (argc - 3);
}

int	get_number_of_pipes(int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		return (argc - 5);
	return (argc - 4);
}

void	close_pipes(int *fd, int num_pipes)
{
	int	i;
	int	lim;

	i = 0;
	lim = num_pipes * 2;
	while (i < lim)
	{
		close(fd[i]);
		i++;
	}
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*join;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (0);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (0);
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
	{
		free(s1);
		return (0);
	}
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (join);
}
