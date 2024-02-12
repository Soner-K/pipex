/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:56 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/12 20:30:27 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// static void	files_handler_here_doc(t_process *dt)
// {
// 	if (dt->id == 0)
// 	{
// 		if (dup2(dt->fds[0], STDIN_FILENO) == -1)
// 			error_handler("27");
// 		if (dup2(dt->fds[1], STDOUT_FILENO) == -1)
// 			error_handler("29");
// 		close_handler(4, dt->fds[0], dt->fds[1], dt->fd_in, dt->fd_out);
// 		return ;
// 	}
// 	if (dup2(dt->fds[0], STDIN_FILENO) == -1)
// 		error_handler("37");
// 	if (dup2(dt->fd_out, STDOUT_FILENO) == -1)
// 		error_handler("39");
// 	close_handler(4, dt->fds[0], dt->fds[1], dt->fd_in, dt->fd_out);
// 	return ;
// }

void	store_in_here_doc(char *del, int fds[2])
{
	char	*str;
	size_t	len_del;

	str = get_next_line(0, 0);
	if (!str)
		error_handler("");
	ft_putstr_fd(str, fds[1]);
	len_del = ft_strlen(del);
	while (ft_strncmp(del, str, ft_strlen(str) - 1) || ft_strlen(str)
		- 1 != len_del)
	{
		free(str);
		str = get_next_line(0, 0); // modif parametre
		if (!str)
			error_handler("");
		ft_putstr_fd(str, fds[1]);
	}
	if (str)
		free(str);
}

//////// PB : LES ECRITURES DE GNL SONT COMPTEES ALORS QUE DEVRAIT PAS

void	pipe_here_doc(int argc, char **argv, char **envp, t_process *data)
{
	data->fd_in = open(argv[1], CR | R_W | O_TRUNC, 0644);
	if (data->fd_in == -1)
		error_handler("here_doc");
	data->fd_out = open(argv[argc - 1], CR | R_W | AP, 0644);
	if (data->fd_out == -1)
		perror("open");
	if (pipe(data->fds) == -1)
		perror("pipe");
	data->id = fork();
	if (data->id == -1)
		perror("fork");
	if (data->id == 0)
	{
		store_in_here_doc(argv[2], data->fds);
		dup2(data->fds[1], STDOUT_FILENO);
	}
	if (data->id == 0)
		exec_one(argv[3], envp, data);
	else
	{
		waitpid(data->id, 0, 0);
		dup2(data->fds[0], STDIN_FILENO);
		exec_one(argv[4], envp, data);
	}
}
