/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:07:37 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 11:30:18 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*this function checks the character after a % and does the necessary accordingly*/
static void	ft_check_and_print(const char **str, char c, va_list arg, int *size)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(arg, int), 1);
		(*size)++;
	}
	if (c == 's')
		ft_putstr(va_arg(arg, char *), size);
	if (c == 'i' || c == 'd')
		ft_putnbr_long((int) va_arg(arg, int), size);
	if (c == 'x' || c == 'X')
		to_hex(va_arg(arg, unsigned int), c, 0, size);
	if (c == 'p')
		to_hex(va_arg(arg, unsigned long), c, 1, size);
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*size)++;
	}
	if (c == 'u')
		ft_putnbr_long((unsigned int) va_arg(arg, unsigned int), size);
	(*str) += 2;
}

/*my printf, which writes str until a %, then check 
what the character is and write whats needs to be written*/
int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		size;

	if (!str)
		return (-1);
	va_start(arg, str);
	size = 0;
	while (*str)
	{
		if (*str == '%')
			ft_check_and_print(&str, *(str + 1), arg, &size);
		else
		{
			ft_putchar_fd(*str, 1);
			str++;
			size++;
		}
	}
	va_end(arg);
	return (size);
}
