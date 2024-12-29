/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:16:54 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/11 20:17:06 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_string(char *str)
{
	int		n_ret;

	n_ret = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (*str)
	{
		ft_putchar_fd(*str, 1);
		str++;
		n_ret++;
	}
	return (n_ret);
}
