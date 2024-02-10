/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:56:27 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/10 20:06:49 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	memory_handler(t_path *utils)
{
	free(utils->path);
	free_arrs((void **)utils->cmds);
}

char	pipe_it(char *cmd, char **envp)
{
	t_path		utils;
	t_process	data;

	if (pipe(data.fds) == -1)
		return (-1);
	data.id = fork();
	if (data.id == -1)
		return (-1);
	utils.cmds = ft_split(cmd, ' ');
	if (!utils.cmds)
		return (-1);
	utils.path = find_path(envp, utils.cmds[0], 0);
	if (!utils.path)
	{
		free_arrs((void **)utils.cmds);
		return (-1);
	}
	ft_exec(utils.cmds, utils.path, envp, &data);
	return (1);
}

void	ft_exec(char **cmds, char *path, char **envp, t_process *data)
{
	if (data->id == 0)
	{
		close(data->fds[0]);
		dup2(data->fds[1], STDOUT_FILENO);
		close(data->fds[1]);
	}
	else
	{
		close(data->fds[1]);
		dup2(data->fds[0], STDIN_FILENO);
		close(data->fds[0]);
	}
	execve(path, cmds, envp);
	free_arrs((void **)cmds);
	free(path);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_process main_data;

	if (argc > 5)
	{
	}
}