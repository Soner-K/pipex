/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:31:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 09:09:42 by sokaraku         ###   ########.fr       */
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

static void	store_in_here_doc(char *del, t_process *data, int fd_tmp)
{
	char	*str;
	long	len_del;
	long	len_str;

	str = NULL;
	len_del = ft_strlen(del);
	len_str = 0;
	// fd_tmp = open("tmp", O_CREAT | O_RDWR, 0644);
	while ((len_str - 1 != len_del) || ft_strncmp(del, str, len_str - 1))
	{
		if (str)
			free(str);
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0, 0); // modif parametre
		if (!str)
			error_handler("", data, 0, 0); // print_and_exit
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
// 	if (first_cmd == 0)
// 	{
// 	}
// 	if (dup2(fds[1], STDOUT_FILENO) == -1)
// 		error_handler("dup2", data, 0);
// 	{
// 	}
// 	else
// 	{
// 		// dup2(fds[0], STDIN_FILENO);
// 		// dup2(fds[1], STDOUT_FILENO);
// 		if (dup2(fd_out, STDOUT_FILENO) == -1)
// 			error_handler("dup2", data, 0);
// 	}
// 	// first_cmd++;m
// 	close_handler(4, fds[0], fds[1], fd_in, fd_out);
// 	ft_exec(envp, path, cmds);
// }

// void	here_doc(char *del, t_process *data, int argc, char **argv, char **envp)
// {
// 	int		id;
// 	char	*path;
// 	char	**cmds;
// 	int		fd_tmp;
// 	int		out;
// 	int		fds[2];

// 	(void)data;
// 	fd_tmp = open("tmp", O_CREAT | O_RDWR, 0644);
// 	out = open(argv[argc - 1], O_RDWR);
// 	pipe(fds);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		store_in_here_doc(del, data, fd_tmp);
// 		cmds = ft_split(argv[3], ' ');
// 		path = find_path(*cmds, envp, 0);
// 		dup2(fds[0], fd_tmp);
// 		dup2(fds[1], STDOUT_FILENO);
// 		close_handler(2, fds[0], fds[1]);
// 		ft_exec(envp, path, cmds);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		dup2(fds[1], out);
// 		id = fork();
// 		if (id == 0)
// 		{
// 			cmds = ft_split(argv[4], ' ');
// 			path = find_path(*cmds, envp, 0);
// 			dup2(fds[0], STDIN_FILENO);
// 			close_handler(2, fds[0], fds[1]);
// 			ft_exec(envp, path, cmds);
// 		}
// 	}

// 	close_handler(4, fds[0], fds[1]);
// }

void	test2(char **argv, char **envp, t_process *data)
{
	t_paths	utils;

	// wait(NULL);
	data->id = fork();
	if (data->id == -1)
		error_handler("fork", data, 1, 0);
	if (data->id == 0)
	{
		if (dup2(data->fds[0], STDIN_FILENO) == -1)
			error_handler("dup2", data, 1, 0);
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			error_handler("dup2", data, 1, 0);
		utils.cmds = ft_split(argv[4], ' ');
		if (!utils.cmds || !utils.cmds[0]) // check leak avec ""
			error_handler(ER_MALLOC, data, 0, 0);
		utils.path = find_path(*utils.cmds, envp, 0, data);
		if (!utils.path)
			error_handler(ER_MALLOC, data, 0, 1, utils.cmds);
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[0]);
		ft_exec(envp, utils.path, utils.cmds);
	}
	else
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
	unlink(".tmp");
}
void	test(char **argv, char **envp, t_process *data)
{
	t_paths	utils;

	if (pipe(data->fds) == -1)
		error_handler("pipe", data, 1, 0);
	data->id = fork();
	if (data->id == -1)
		error_handler("fork", data, 1, 0);
	if (data->id == 0)
	{
		store_in_here_doc(argv[2], data, data->fd_in);
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			error_handler("dup2", data, 1, 0);
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			error_handler("dup2", data, 1, 0);
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
		utils.cmds = ft_split(argv[3], ' ');
		if (!utils.cmds || !utils.cmds[0])
			error_handler(ER_MALLOC, data, 0, 0);
		utils.path = find_path(*utils.cmds, envp, 0, data);
		if (!utils.path)
			error_handler(ER_MALLOC, data, 0, 0, utils.cmds);
		ft_exec(envp, utils.path, utils.cmds);
	}
	else
	{
		wait(NULL);
		close(data->fds[1]);
		test2(argv, envp, data);
		// close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
	}
}

// void	here_doc(char *del, t_process *data, int argc, char **argv, char **envp)
// {
// 	int		id;
// 	char	*path;
// 	char	**cmds;
// 	int		fd_tmp;
// 	int		out;
// 	int		test;
// 	int		fds[2];

// 	fd_tmp = open("tmp", O_CREAT | O_RDWR, 0644);
// 	out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, O_APPEND, 0644);
// 	// Open with O_CREAT and O_TRUNC
// 	pipe(fds);
// 	test = fork();
// 	if (test == 0)
// 	{
// 		close(fds[0]); // Close unused read end of pipe
// 		store_in_here_doc(del, data, fd_tmp);
// 		dup2(fd_tmp, STDIN_FILENO);
// 		close(fd_tmp);
// 		cmds = ft_split(argv[3], ' ');
// 		path = find_path(*cmds, envp, 0);
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]); // Close write end of pipe after redirection
// 		ft_exec(envp, path, cmds);
// 	}
// 	else
// 	{
// 		// waitpid(-1, NULL, WNOHANG);
// 		wait(NULL);
// 		close(fds[1]); // Close unused write end of pipe
// 		// dup2(fd_tmp, STDIN_FILENO);
// 		close(fd_tmp); // Close fd_tmp after redirection
// 		id = fork();
// 		wait(NULL);
// 		if (id == 0)
// 		{
// 			// waitpid(test, NULL, 0);
// 			wait(NULL);
// 			cmds = ft_split(argv[4], ' ');
// 			path = find_path(*cmds, envp, 0);
// 			dup2(fds[0], STDIN_FILENO);
// 			close(fds[0]); // Close read end of pipe after redirection
// 			// dup2(fds[1], STDOUT_FILENO);
// 			close(fds[1]);
// 			ft_exec(envp, path, cmds);
// 		}
// 	}
// 	close(fd_tmp); // Close fd_tmp in parent process
// 	close(fds[0]); // Close fds in parent process
// 	close(fds[1]);
// 	unlink("tmp");
// }

// void	here_doc(char *del, t_process *data, int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	int pid1;
// 	// int pid2;
// 	if (pipe(fds) == -1)
// 		error_handler("pipe", data, 0);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		// dup2(fds[0], )
// 		store_in_here_doc(del, fds, data);
// 		// dup2(fds[0], STDIN_FILENO);
// 		dup2(fds[1], STDOUT_FILENO);
// 		execve(find_path(argv[3], envp, 0), ft_split(argv[3], ' '), envp);
// 	}
// 	else
// 	{
// 		close(fds[1]);
// 		dup2(fds[0], STDIN_FILENO);
// 		wait(NULL);
// 	}
// 	// // wait(NULL);
// 	// // else
// 	// // {

// 	// // 	dup2(fds[0], STDIN_FILENO);
// 	// // }
// 	// pid2 = fork();
// 	// if (pid1 == 0)
// 	// {
// 	// 	dup2(fds[1], STDOUT_FILENO);
// 	// 	execve(find_path(argv[4], envp, 0), ft_split(argv[4], ' '), envp);
// 	// }
// 	// while (wait(NULL) > 0)
// 	// 	;
// 	// // else
// 	// // 	dup2(fds[1], fd_out);
// 	// close_handler(4, fds[0], fds[1], fd_in, fd_out);
// }