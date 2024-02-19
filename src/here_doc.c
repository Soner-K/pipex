/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:31:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/19 19:46:46 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	store_in_here_doc(char *del, int fds[2], t_process *data)
// {
// 	char	*str;
// 	long	len_del;
// 	long	len_str;
// 	int		fd_tmp;

// 	str = NULL;
// 	len_del = ft_strlen(del);
// 	len_str = 0;
// 	fd_tmp = open("tmp", O_CREAT | O_RDWR, 0644);
// 	while ((len_str - 1 != len_del) || ft_strncmp(del, str, len_str - 1))
// 	{
// 		if (str)
// 			free(str);
// 		ft_putstr_fd("pipe heredoc> ", 0);
// 		str = get_next_line(0, 0); // modif parametre
// 		if (!str)
// 			error_handler("malloc", data, 0);
// 		ft_putstr_fd(str, fds[1]);
// 		len_str = ft_strlen(str);
// 	}
// 	if (str)
// 		free(str);
// 	// close_handler(2, fds[0], fds[1]);
// }

static void	store_in_here_doc(char *del, t_process *data)
{
	char	*str;
	long	len_del;
	long	len_str;
	int		fd_tmp;

	str = NULL;
	len_del = ft_strlen(del);
	len_str = 0;
	fd_tmp = open("tmp", O_CREAT | O_RDWR, 0644);
	while ((len_str - 1 != len_del) || ft_strncmp(del, str, len_str - 1))
	{
		if (str)
			free(str);
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0, 0); // modif parametre
		if (!str)
			error_handler("malloc", data, 0);
		ft_putstr_fd(str, fd_tmp);
		len_str = ft_strlen(str);
	}
	if (str)
		free(str);
	// close_handler(2, fds[0], fds[1]);
}
// void	child2(char *to_do, char **envp, char last, t_process *data)
// {
// 	char	*path;
// 	char	**cmds;

// 	cmds = ft_split(to_do, ' ');
// 	path = find_path(*cmds, envp, 0);
// 	if (data->first_cmd == 0)
// 	{
// 	}
// 	if (dup2(data->fds[1], STDOUT_FILENO) == -1)
// 		error_handler("dup2", data, 0);
// 	{
// 	}
// 	else
// 	{
// 		// dup2(data->fds[0], STDIN_FILENO);
// 		// dup2(data->fds[1], STDOUT_FILENO);
// 		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
// 			error_handler("dup2", data, 0);
// 	}
// 	// data->first_cmd++;m
// 	close_handler(4, data->fds[0], data->fds[1], data->fd_in, data->fd_out);
// 	ft_exec(envp, path, cmds);
// }

void	here_doc(char *del, t_process *data, int argc, char **argv, char **envp)
{
	int		id;
	char	*path;
	char	**cmds;
	int		fd_tmp;

	(void)argc;
	fd_tmp = open("tmp", O_RDWR, 0644);
	pipe(data->fds);
	id = fork();
	if (id == 0)
	{
		store_in_here_doc(del, data);
		cmds = ft_split(argv[3], ' ');
		path = find_path(*cmds, envp, 0);
		dup2(data->fds[0], fd_tmp);
		dup2(data->fds[1], STDOUT_FILENO);
		ft_exec(envp, path, cmds);
	}
	// else
	// {
	// 	dup2(data->fds[0], STDIN_FILENO);
	// }
	close_handler(4, data->fds[0], data->fds[1], data->fd_in, data->fd_out);
}
// void	here_doc(char *del, t_process *data, int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	int pid1;
// 	// int pid2;
// 	if (pipe(data->fds) == -1)
// 		error_handler("pipe", data, 0);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		// dup2(data->fds[0], )
// 		store_in_here_doc(del, data->fds, data);
// 		// dup2(data->fds[0], STDIN_FILENO);
// 		dup2(data->fds[1], STDOUT_FILENO);
// 		execve(find_path(argv[3], envp, 0), ft_split(argv[3], ' '), envp);
// 	}
// 	else
// 	{
// 		close(data->fds[1]);
// 		dup2(data->fds[0], STDIN_FILENO);
// 		wait(NULL);
// 	}
// 	// // wait(NULL);
// 	// // else
// 	// // {

// 	// // 	dup2(data->fds[0], STDIN_FILENO);
// 	// // }
// 	// pid2 = fork();
// 	// if (pid1 == 0)
// 	// {
// 	// 	dup2(data->fds[1], STDOUT_FILENO);
// 	// 	execve(find_path(argv[4], envp, 0), ft_split(argv[4], ' '), envp);
// 	// }
// 	// while (wait(NULL) > 0)
// 	// 	;
// 	// // else
// 	// // 	dup2(data->fds[1], data->fd_out);
// 	// close_handler(4, data->fds[0], data->fds[1], data->fd_in, data->fd_out);
// }