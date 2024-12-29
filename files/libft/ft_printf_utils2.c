/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:17:12 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/11 20:17:13 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_int(int n)
{
	char	*str;
	int		i;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	free(str);
	return (i);
}

int	print_unsigned(unsigned int n)
{
	int	n_ret;

	if (n < 10)
	{
		ft_putchar_fd(n + '0', 1);
		return (1);
	}
	else
	{
		n_ret = 1 + print_unsigned(n / 10);
		ft_putchar_fd(n % 10 + '0', 1);
		return (n_ret);
	}
}

int	print_hex(unsigned long n, char *dict)
{
	int		n_ret;

	if (n < 16)
	{
		ft_putchar_fd(dict[n], 1);
		return (1);
	}
	else
	{
		n_ret = 1 + print_hex(n / 16, dict);
		ft_putchar_fd(dict[n % 16], 1);
		return (n_ret);
	}
}

int	print_pointer(void *p)
{
	unsigned long	n;

	if (!p)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	n = (unsigned long)p;
	ft_putchar_fd('0', 1);
	ft_putchar_fd('x', 1);
	return (2 + print_hex(n, "0123456789abcdef"));
}
