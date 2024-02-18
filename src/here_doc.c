/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:31:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/18 21:50:33 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	store_in_here_doc(char *del, int fds[2], t_process *data)
{
	char *str;
	size_t len_del;

	str = get_next_line(0, 0);
	if (!str)
		error_handler("malloc", data, 0);
	ft_putstr_fd(str, fds[1]);
	len_del = ft_strlen(del);
	while (ft_strncmp(del, str, ft_strlen(str) - 1) || ft_strlen(str)
		- 1 != len_del)
	{
		free(str);
		str = get_next_line(0, 0); // modif parametre
		if (!str)
			error_handler("malloc", data, 0);
		ft_putstr_fd(str, fds[1]);
	}
	if (str)
		free(str);
	// close_handler(2, fds[0], fds[1]);
}

void	here_doc(char *del, t_process *data, int argc, char **argv, char **envp)
{
	if (pipe(data->fds) == -1)
		error_handler("pipe", data, 0);
	store_in_here_doc(del, data->fds, data);
	data->id = fork();
	if (data->id == -1)
		error_handler("fork", data, 0);
	pipex(argc - 1, argv, envp, data);
}