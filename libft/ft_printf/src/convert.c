/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:12:23 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 10:38:50 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*a putnbr that receives a long (so that it can deal with both INT_MIN and UNSIGNED_INT_MAX)
with also a pointer to size that is increased by each call to the ft_putnbr_long function*/
void	ft_putnbr_long(long nb, int	*size)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar_fd('-', 1);
		(*size)++;
	}
	if (nb / 10)
	{
		(*size)++;
		ft_putnbr_long(nb / 10, size);
	}
	else
		(*size)++;
	ft_putchar_fd((nb % 10) + '0', 1);
}


/*Classic ft_putstr but whit a size pointer that acts as a counter of the characters written,
just like in ft_putnbr_long>*/
void	ft_putstr(char *str, int *size)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		(*size) += 6;
		return ;
	}
	(*size) += ft_strlen(str);
	while (*str)
		ft_putchar_fd(*str++, 1);
}

/*basically a putnbr but in hexadecimal format
the format is modified in function of the character c sent (x or X)
p is a binary used only in the first call of the function. If it is 1
then a 0x needs to be written for writing an adress of a void pointer (in hex value)*/
void	to_hex(unsigned long nb, char c, char p, int *size)
{
	char	*base;

	if (nb == 0 && p == 1)
	{
		(*size) += 5;
		ft_putstr_fd("(nil)", 1);
		return ;
	}
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (p == 1)
	{
		(*size) += 2;
		ft_putstr_fd("0x", 1);
	}
	if (nb / 16)
	{
		(*size)++;
		to_hex(nb / 16, c, 0, size);
	}
	else
		(*size)++;
	ft_putchar_fd(base[nb % 16], 1);
}
