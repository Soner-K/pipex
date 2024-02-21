/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:31:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 11:29:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	store_in_here_doc(char *del, t_process *data, int fd_tmp)
{
	char	*str;
	long	len_del;
	long	len_str;

	str = NULL;
	len_del = ft_strlen(del);
	len_str = 0;
	while ((len_str - 1 != len_del) || ft_strncmp(del, str, len_str - 1))
	{
		if (str)
			free(str);
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0); // modif parametre
		if (!str)
			return (data->use_p = 0, error_handler("", data, 0));
		ft_putstr_fd(str, fd_tmp);
		len_str = ft_strlen(str);
	}
	if (str)
		free(str);
}

static void	here_doc_following(char **argv, char **envp, t_process *data)
{
	t_paths	utils;

	data->id = fork();
	if (data->id == -1)
		error_handler("fork", data, 0);
	if (data->id == 0)
	{
		if (dup2(data->fds[0], STDIN_FILENO) == -1)
			error_handler("dup2", data, 0);
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			error_handler("dup2", data, 0);
		utils.cmds = ft_split(argv[4], ' ');
		if (!utils.cmds || !utils.cmds[0])
			return (data->use_p = 0, error_handler(MKO, data, 0));
		utils.path = find_path(*utils.cmds, envp, 0, data);
		if (!utils.path)
			return (data->use_p = 0, error_handler(MKO, data, 1, utils.cmds));
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[0]);
		ft_exec(envp, utils.path, utils.cmds);
	}
	else
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
	unlink(".tmp");
}

void	here_doc(char **argv, char **envp, t_process *data)
{
	t_paths	utils;

	if (pipe(data->fds) == -1)
		error_handler("pipe", data, 0);
	data->id = fork();
	if (data->id == -1)
		error_handler("fork", data, 0);
	if (data->id == 0)
	{
		store_in_here_doc(argv[2], data, data->fd_in);
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			error_handler("dup2", data, 0);
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			error_handler("dup2", data, 0);
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
		utils.cmds = ft_split(argv[3], ' ');
		if (!utils.cmds || !utils.cmds[0])
			return (data->use_p = 0, error_handler(MKO, data, 0));
		utils.path = find_path(*utils.cmds, envp, 0, data);
		if (!utils.path)
			return (data->use_p = 0, error_handler(MKO, data, 1, utils.cmds));
		ft_exec(envp, utils.path, utils.cmds);
	}
	wait(NULL);
	return (close(data->fds[1]), here_doc_following(argv, envp, data));
}
