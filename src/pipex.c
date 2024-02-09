/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:25:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/09 19:07:45 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_process(char *cmd, char **envp, t_process *data)
{
	t_path	utils;
	
	utils.cmds = ft_split(cmd, ' ');
	if (!utils.cmds)
	{
		perror("malloc (exec_process)");
		exit(1);
	}
	utils.path = find_path(envp, utils.cmds[0], 0);
	if (!utils.path) // free?
	{
		free_arrs((void **) utils.cmds);
		perror("malloc (exec_process)");
		exit(1);
	}
	if (data->id == 0)
	{
		close(data->fds[0]);
		dup2(data->fd_infile, STDIN_FILENO);
		dup2(data->fds[1], STDOUT_FILENO);
		close(data->fds[1]);
		close(data->fd_infile);
		close(data->fd_outfile);
	}
	else
	{
		close(data->fds[1]);
		dup2(data->fds[0], STDIN_FILENO);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fds[0]);
		close(data->fd_outfile);
		close(data->fd_infile);
	}
	execve(utils.path, utils.cmds, envp);
	free(utils.path);
	free_arrs((void **)utils.cmds);
	perror("execve");
	exit(1);
}

// un fichier non ferme si seul un des deux echecs tention
int	main(int argc, char **argv, char **envp)
{
	t_process data;

	if (argc != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	data.fd_infile = open(argv[1], R_OK | O_CREAT);
	data.fd_outfile = open(argv[argc - 1], W_OK | O_CREAT);
	if (data.fd_infile == -1 || data.fd_outfile == -1)
	{
		perror("open");
		exit(1);
	}
	if (pipe(data.fds) == -1)
	{
		perror("pipe");
		exit(1);
	}
	data.id = fork();
	if (data.id == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (data.id == 0)
		exec_process(argv[2], envp, &data);
	wait(NULL);
	exec_process(argv[3], envp, &data);
	return (0);
}