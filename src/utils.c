/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:11:57 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/16 18:56:19 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(char *msg, t_process *data, int n, ...)
{
	va_list	arg;

	perror(msg);
	if (!n)
	{
		va_end(arg);
		exit(EXIT_FAILURE);
	}
	va_start(arg, n);
	while (n--)
		free_arrs((void **) va_arg(arg, char **));
	va_end(arg);
	if (data)
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
	exit(EXIT_FAILURE);
}

void	ft_exec(char **envp, char *path, char **cmds)
{
	execve(path, cmds, envp);
	free(path);
	free_arrs((void **)cmds);
	error_handler("execve", NULL, 0);
}

// int	main(int argc, char **av, char **envp)
// {
// 	(void)argc;
// 	char *path;

// 	path = find_path(av[1], envp, 0);
// 	printf("%s\n\n\n\n", path);
// 	// av++;
// 	// execve(path, ++av, envp);
// 	free(path);
// 	perror("");
// 	// if (path)
// 	// 	free(path);
// }