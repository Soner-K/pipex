/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:25:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/10 18:06:49 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// check fds dans valgrnd
static void	files_handler(t_process *data, char child)
{
	if (child == 1)
	{
		close(data->fds[0]);
		if (dup2(data->fd_infile, STDIN_FILENO) == -1)
			error_handler("dup");
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			error_handler("dup");
		close(data->fds[1]);
		close(data->fd_infile);
		close(data->fd_outfile);
		return ;
	}
	close(data->fds[1]);
	if (dup2(data->fds[0], STDIN_FILENO) == -1)
		error_handler("dup");
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		error_handler("dup");
	close(data->fds[0]);
	close(data->fd_outfile);
	close(data->fd_infile);
	return ;
}

char	exec_process(char *cmd, char **envp, t_process *data)
{
	t_path	utils;

	utils.cmds = ft_split(cmd, ' ');
	if (!utils.cmds)
	{
		// perror("malloc (exec_process)");
		return (-1);
	}
	utils.path = find_path(envp, utils.cmds[0], 0);
	if (!utils.path) // free?
	{
		free_arrs((void **)utils.cmds);
		// perror("malloc (exec_process)");
		return (-1);
	}
	if (data->id == 0)
		files_handler(data, 1);
	else
		files_handler(data, 0);
	execve(utils.path, utils.cmds, envp);
	free(utils.path);
	free_arrs((void **)utils.cmds);
	// perror("execve");
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_process	data;
	int			info_pid;

	if (argc != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	data.fd_infile = open(argv[1], R_OK);
	if (data.fd_infile == -1)
		error_handler("");
	data.fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data.fd_outfile == -1)
		error_handler("");
	if (pipe(data.fds) == -1)
		error_handler("");
	data.id = fork();
	if (data.id == -1)
		error_handler("");
	else if (data.id == 0)
		if (exec_process(argv[2], envp, &data) == -1)
			exit(EXIT_FAILURE);
	waitpid(data.id, &info_pid, WNOHANG);
	if (exec_process(argv[3], envp, &data) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
