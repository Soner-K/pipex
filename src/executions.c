/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:55:05 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/11 14:00:50 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Duplicates and close the necessary files when dealing with one pipe.
 * @param data A pointer to a structure containing different variables,
 * including pipe's fds and the infile's and outfile's fd.
 * @returns void.
 */
static void	files_handler(t_process *data)
{
	if (data->id == 0)
	{
		close(data->fds[0]);
		if (dup2(data->fd_infile, STDIN_FILENO) == -1)
			error_handler("29");
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			error_handler("31");
		close(data->fds[1]);
		close(data->fd_infile);
		close(data->fd_outfile);
		return ;
	}
	close(data->fds[1]);
	if (dup2(data->fds[0], STDIN_FILENO) == -1)
		error_handler("39");
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		error_handler("41");
	close(data->fds[0]);
	close(data->fd_outfile);
	close(data->fd_infile);
	return ;
}

/**
 * @brief Execute a process (used in the mandatory part, i.e only one pipe).
 * @param cmd The path to the command's executable.
 * @param emvp Environment variable.
 * @param data A pointer to a structure containing multiple variables.
 * @returns -1 in case of an error.
 */
static char	exec_mandatory(char *cmd, char **envp, t_process *data)
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
	if (data->config == MANDATORY)
		files_handler(data);
	execve(utils.path, utils.cmds, envp);
	free(utils.path);
	free_arrs((void **)utils.cmds);
	// perror("execve");
	return (-1);
}

/**
 * @brief Executes one pipe, doing the I/O redirections with the fds.
 * @param cmds An array of strings containing the command and its options.
 * @param path The path to a command's executable.
 * @param emvp Environment variable.
 * @param data A pointer to a structure containing multiple variables.
 * @returns void.
 */
static void	exec_mpipes(char **cmds, char *path, char **envp, t_process *data)
{
	if (data->id == 0)
	{
		close(data->fds[0]);
		dup2(data->fds[1], STDOUT_FILENO);
		close(data->fds[1]);
		execve(path, cmds, envp);
		free_arrs((void **)cmds);
		free(path);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(data->fds[1]);
		dup2(data->fds[0], STDIN_FILENO);
		close(data->fds[0]);
	}
}

/**
 * @brief Executes one pipe.
 * @param cmd The command to execute.
 * @param emvp Environment variable.
 * @returns -1 if there is an error.
 */
static char	pipe_it(char *cmd, char **envp)
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
	exec_mpipes(utils.cmds, utils.path, envp, &data);
	return (1);
}

/**
 * @brief
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variable.
 * @param data A pointer to a structure containing multiple variables.
 * @returns void.
 */
void	ft_exec(int argc, char **argv, char **envp, t_process *data)
{
	int	i;

	i = 2;
	if (data->config == MANDATORY)
	{
		if (data->id == 0)
			if (exec_mandatory(argv[2], envp, data) == -1)
				exit(EXIT_FAILURE);
		waitpid(data->id, data->info_id, WNOHANG);
		if (exec_mandatory(argv[3], envp, data) == -1)
			exit(EXIT_FAILURE);
	}
	else if (data->config == MULTIPLE_PIPES)
	{
		while (i < argc - 2)
			pipe_it(argv[i++], envp);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_infile);
		close(data->fd_outfile);
		exec_mandatory(argv[i], envp, data);
	}
}
