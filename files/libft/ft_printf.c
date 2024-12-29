/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:30:24 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/11 10:30:26 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_format(char const *format, va_list args)
{
	if (*format == 'c')
		return (print_char(va_arg(args, int)));
	else if (*format == 's')
		return (print_string(va_arg(args, char *)));
	else if (*format == 'd' || *format == 'i')
		return (print_int(va_arg(args, int)));
	else if (*format == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (*format == 'x')
		return (print_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (*format == 'X')
		return (print_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (*format == 'p')
		return (print_pointer(va_arg(args, void *)));
	else if (*format == '%')
		return (print_char('%'));
	else
	{
		ft_putchar_fd('%', 1);
		ft_putchar_fd(*format, 1);
		return (2);
	}
}

static int	print_message(char const *format, va_list args)
{
	int		n_ret;
	int		n_aux;

	n_ret = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '\0')
		{
			format++;
			n_aux = print_format(format, args);
			if (n_aux == -1)
				return (-1);
			n_ret += n_aux;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			n_ret++;
		}
		format++;
	}
	return (n_ret);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		n_ret;

	if (!format)
		return (-1);
	va_start(args, format);
	n_ret = print_message(format, args);
	va_end(args);
	return (n_ret);
}
