/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/15 23:28:43 by sokaraku         ###   ########.fr       */
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

// void	pipe_it(char **argv, char **envp, t_process *data)
// {

// }

// void	pipe_it(char **envp, char *path, char **cmds, t_process *data)
// {
// 	int	id;

// 	if (pipe(data->fds) == -1)
// 		error_handler("pipe", NULL, 0);
// 	id = fork();
// 	if (id == -1)
// 		error_handler("fork", NULL, 0);
// 	else if (id == 0 && last == 0)
// 	{
// 		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
// 			return (free(path), error_handler("dup2 1", data, 1, cmds));
// 		if (dup2(data->fd_in, STDIN_FILENO) == -1)
// 			return (free(path), error_handler("dup2 2", data, 1, cmds));
// 		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
// 		ft_exec(envp, path, cmds);
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_process	data;
// 	int			i;
// 	int			id;

// 	(void)argc;
// 	i = 0;
// 	data.fd_in = open(argv[1], O_RDONLY, 0644);
// 	data.fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_RDONLY, 0644);
// 	while (i < 2)
// 	{
// 		pipe(data.fds);
// 		id = fork();
// 		if (id == 0 && i == 0)
// 		{
// 			dup2(data.fds[1], STDOUT_FILENO);
// 			dup2(data.fd_in, STDIN_FILENO);
// 			close_handler(2, data.fds[0], data.fds[1]);
// 			ft_exec(envp, find_path(argv[2], envp, 0), ft_split(argv[2], ' '));
// 		}
// 		if (id == 0 && i == 1)
// 		{
// 			dup2(data.fds[0], STDIN_FILENO);
// 			dup2(data.fd_out, STDOUT_FILENO);
// 			close_handler(2, data.fds[0], data.fds[1]);
// 			ft_exec(envp, find_path(argv[3], envp, 0), ft_split(argv[3], ' '));
// 		}
// 		else
// 		{
// 			dup2(data.fds[0], STDIN_FILENO);
// 			dup2(data.fd_out, STDOUT_FILENO);
// 			close_handler(2, data.fds[0], data.fds[1]);
// 		}
// 		i++;
// 	}
// 	close_handler(2, data.fd_in, data.fd_out);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_process 	data;
// 	int			i;
// 	int			id;

// 	i = 0;
// 	while (i < argc - 3)
// 	{
// 		pipe(data.fds);
// 		id = fork()

// 	}
// }
// void	exec_first(char *path, char **cmds, char **envp)
// {
// 	int	fds[2];
// 	int	id;

// 	pipe(fds);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fds[0]);
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);
// 		ft_exec(envp, path, cmds);
// 	}
// 	else
// 	{
// 		close(fds[1]);
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[2]);
// 	}
// }

// void	exec_second(char *path, char **cmds, char **envp)
// {
// 	int	fds[2];
// 	int	id;

// 	pipe(fds);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fds[0]);
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);
// 		ft_exec(envp, path, cmds);
// 	}
// 	else
// 	{

// 	}
// }

void	child(char *to_do, char **envp, char last, t_process *data)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(to_do, ' ');
	path = find_path(*cmds, envp, 0);
	if (last == 0)
		dup2(data->fds[1], STDOUT_FILENO);
	close_handler(2, data->fds[0], data->fds[1]);
	ft_exec(envp, path, cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_process	data;
	int			i;
	int			id;
	int			j;

	(void)argc;
	i = 0;
	j = 1;
	while (i < 2)
	{
		pipe(data.fds);
		id = fork();
		if (id == 0)
			child(argv[j], envp, i == 1, &data);
		else
		{
			dup2(data.fds[0], STDIN_FILENO);
			close_handler(2, data.fds[0], data.fds[1]);
		}
		i++;
		j++;
	}
	while (wait(NULL) > 0)
		;
}

// dup2(data->fd_out, STDOUT_FILENO) pb car chaque exec ecrira dans le outfile?
// a voir quand la version sera complete
