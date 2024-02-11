/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:56:27 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/11 12:36:24 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	memory_handler(t_path *utils)
{
	free(utils->path);
	free_arrs((void **)utils->cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_process main_data;

	if (argc > 5)
	{
	}
}