/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:19:01 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/14 12:36:07 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	free_arrs(void **arrs)
{
	int	i;

	i = 0;
	if (!arrs)
		return ;
	while (arrs[i])
	{
		free(arrs[i]);
		i++;
	}
	free(arrs[i]);
	free(arrs);
}
