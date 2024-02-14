/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/14 19:31:55 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char **envp, char *path, char **cmds)
{
	execve(path, cmds, envp);
	free(path);
	free_arrs((void **)cmds);
	error_handler("execve", NULL, 0);
}

void	pipe_it(char **envp, char *path, char **cmds, t_process *data)
{
	int	id;

	if (pipe(data->fds) == -1)
		error_handler("pipe", NULL, 0);
	id = fork();
	if (id == -1)
		error_handler("fork", NULL, 0);
	else if (id == 0)
	{
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			return (free(path), error_handler("dup2 1", data, 1, cmds));
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			return (free(path), error_handler("dup2 2", data, 1, cmds));
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
		ft_exec(envp, path, cmds);
	}
	else
	{
		if (dup2(data->fds[0], STDIN_FILENO) == -1)
			return (free(path), error_handler("dup2 3", data, 1, cmds));
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			return (free(path), error_handler("dup2 4", data, 1, cmds));
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
		ft_exec(envp, path, cmds);
	}
}

void	do_one(char **envp, char *cmd, t_process *data)
{
	t_paths	utils;

	utils.cmds = ft_split(cmd, ' ');
	if (!utils.cmds)
		error_handler("malloc", data, 0);
	utils.path = find_path(utils.cmds[0], envp, 0);
	if (!utils.path)
		error_handler("malloc", data, 1, utils.cmds);
	pipe_it(envp, utils.path, utils.all_paths, data);
}

// void	pipe_it(char **envp, char *path, char **cmds, t_process *data, int id)
// {
// 	if (id == 0)
// 	{
// 		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
// 			return (free(path), error_handler("dup2 1", data, 1, cmds));
// 		if (dup2(data->fd_in, STDIN_FILENO) == -1)
// 			return (free(path), error_handler("dup2 2", data, 1, cmds));
// 		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
// 		ft_exec(envp, path, cmds);
// 	}
// 	else
// 	{
// 		if (dup2(data->fds[0], STDIN_FILENO) == -1)
// 			return (free(path), error_handler("dup2 3", data, 1, cmds));
// 		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
// 			return (free(path), error_handler("dup2 4", data, 1, cmds));
// 		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
// 		// ft_exec(envp, path, cmds);
// 	}
// }

// void	do_one(char **envp, char **argv, t_process *data)
// {
// 	t_paths	utils;
// 	int		id;
// 	int		i;
// 	int		j;
	
// 	i = 0;
// 	j = 2;
// 	while (i < 2)
// 	{
// 		if (pipe(data->fds) == -1)
// 			error_handler("pipe", NULL, 0);
// 		id = fork();
// 		if (id == -1)
// 			error_handler("fork", NULL, 0);
// 		utils.path = find_path(argv[j], envp, 0);
// 		if (!utils.path)
// 			error_handler("malloc", data, 0);
// 		utils.cmds = ft_split(argv[j], ' ');
// 		if (!utils.cmds)
// 		{
// 			free(utils.path);
// 			error_handler("malloc", data, 0);
// 		}
// 		pipe_it(envp, utils.path, utils.all_paths, data, id);
// 		i++;
// 		j++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	data.fd_in = open(argv[1], O_RDONLY, 0644);
	data.fd_out = open(argv[argc - 1], O_WRONLY, O_CREAT, O_TRUNC, 0644);
	do_one(envp, argv[2], &data);
	do_one(envp, argv[3], &data);
}
// dup2(data->fd_out, STDOUT_FILENO) pb car chaque exec ecrira dans le otufile?
// a voir quand la version sera complete