/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:36:13 by ffierro-          #+#    #+#             */
/*   Updated: 2025/01/21 14:09:16 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	count_words(char const *s, int i)
{
	int		words;
	char	skip_char;

	words = 0;
	while (s && s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
		{
			words++;
			if (s[i] == '"' || s[i] == '\'')
			{
				skip_char = s[i++];
				while (s[i] != skip_char && s[i] != '\0')
					i++;
			}
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
				i++;
		}
	}
	return (words);
}

static char	**free_malloc(char **strs, int i)
{
	while (--i >= 0)
		free (strs[i]);
	free (strs);
	return (0);
}

static size_t	get_size(char const *s)
{
	size_t	size;
	char	skip_char;

	if (*s == '\'' || *s == '"')
	{
		size = 1;
		skip_char = *s;
		while (s[size] && s[size] != skip_char)
			size++;
		if (s[size] == skip_char)
			size--;
	}
	else
	{
		size = 0;
		while (s[size] && s[size] != ' '
			&& s[size] != '\t' && s[size] != '\n')
			size++;
	}
	return (size);
}

static char	**split_cad(char const *s, char **strs, int i)
{
	size_t	size;
	int		j;

	j = 0;
	while (s[j])
	{
		while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
			j++;
		if (s[j])
		{
			size = get_size(&s[j]);
			if (s[j] == '\'' || s[j] == '"')
				strs[++i] = ft_substr(s, ++j, size++);
			else
				strs[++i] = ft_substr(s, j, size);
			if (!strs[i])
				return (free_malloc(strs, i));
			j += size;
			if (s[j] == '\'' || s[j] == '"')
				j++;
		}
	}
	strs[++i] = 0;
	return (strs);
}

char	**parse_command(char *s)
{
	char	**strs;

	if (!s)
		return (0);
	strs = (char **)malloc((count_words(s, 0) + 1) * sizeof (char *));
	if (!strs)
		return (0);
	return (split_cad(s, strs, -1));
}
