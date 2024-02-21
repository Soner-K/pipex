/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:11:57 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 08:54:16 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Handles error cases : print an error message,
 * close files descriptor and free array of strings if needed.
 * @param msg The message to print.
 * @param data A structure containing file descriptors.
 * @param n	The number of string arrays to free.
 * @param ... The array(s) of string(s).
 * @returns
 */
void	error_handler(char *msg, t_process *data, char use_p, int n, ...)
{
	va_list	arg;

	if (use_p == 1)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	if (!access(".tmp", F_OK))
		unlink(".tmp");
	// if (!n)
	// {
	// 	va_end(arg);
	// 	exit(EXIT_FAILURE);
	// }
	va_start(arg, n);
	while (n--)
		free_arrs((void **)va_arg(arg, char **));
	va_end(arg);
	if (data)
		close_handler(4, data->fd_in, data->fd_out, *data->fds, data->fds[1]);
	exit(EXIT_FAILURE);
}

/**
 * @brief Executes a program given its path, the options
 * and the environment variable.
 * @param envp The environment variable.
 * @param path The path to an executable.
 * @param cmds The command and its options.
 * @returns void. If an error occured in execve, the strings are freed.
 */
void	ft_exec(char **envp, char *path, char **cmds)
{
	execve(path, cmds, envp);
	free(path);
	free_arrs((void **)cmds);
	error_handler("execve", NULL, 1, 0);
}
/**
 * @brief
 * @param
 * @param
 * @param
 * @param
 * @returns void.
 */
void	pipex(int argc, char **argv, char **envp, t_process *data)
{
	int	i;

	i = 0;
	data->first_cmd = 0;
	while (i < argc - 3)
	{
		if (pipe(data->fds) == -1)
			error_handler("pipe", data, 1, 0);
		data->id = fork();
		if (data->id == -1)
			error_handler("fork", data, 1, 0);
		if (data->id == 0)
			child(argv[i + 2], envp, i + 1 == (argc - 3), data);
		else
		{
			dup2(data->fds[0], STDIN_FILENO);
			close_handler(2, data->fds[0], data->fds[1]);
		}
		i++;
		data->first_cmd++;
	}
}
/**
 * @brief
 * @param
 * @param
 * @param
 * @param
 * @returns
 */
void	child(char *to_do, char **envp, char last, t_process *data)
{
	char	*path;
	char	**cmds;

	if (!to_do || !to_do[0])
		error_handler("EEE", data, 0, 0);
	cmds = ft_split(to_do, ' ');
	// if (!cmds || !cmds[0])
	// 	exit(EXIT_FAILURE);
	path = find_path(cmds[0], envp, 0, data);
	if (!path || !path[0])
		error_handler("dup2", data, 1, 1, cmds);
	if (last == 0)
	{
		if (data->first_cmd == 0)
		{
			if (dup2(data->fd_in, STDIN_FILENO) == -1)
				return (free(path), error_handler("dup2", data, 1, 1, cmds));
			// if (dup2(data->fds[0], data->fd_in) == -1)
			// 	error_handler("dup2", data, 0);
		}
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			return (free(path), error_handler("dup2", data, 1, 1, cmds));
	}
	else
	{
		// dup2(data->fds[0], STDIN_FILENO);
		// dup2(data->fds[1], STDOUT_FILENO);
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			return (free(path), error_handler("dup2", data, 1, 1, cmds));
	}
	// data->first_cmd++;m
	close_handler(4, data->fds[0], data->fds[1], data->fd_in, data->fd_out);
	ft_exec(envp, path, cmds);
}
/**
 * @brief
 * @param
 * @param
 * @param
 * @returns
 */
void	check_and_open(int argc, char **argv, t_process *data)
{
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
	{
		data->here_doc = 1;
		data->fd_in = open(".tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (data->fd_in == -1)
			error_handler("here_doc", NULL, 1, 0);
		data->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data->fd_out == -1)
			return (close(data->fd_in), exit(EXIT_FAILURE));
		return ;
	}
	data->here_doc = 0;
	data->fd_in = open(argv[1], O_RDONLY, 0644);
	if (data->fd_in == -1)
		print_exit("Failed to open infile");
	data->fd_out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd_out == -1)
		return (close(data->fd_in), exit(EXIT_FAILURE));
}

char	check_for_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}

// int    wait_childs(int pid)
// {
//     int    wstatus;
//     int    code;

//     code = EXIT_FAILURE;
//     while (errno != ECHILD)
//         if (wait(&wstatus) == pid && WIFEXITED(wstatus))
//             code = WEXITSTATUS(wstatus);
//     if (pid == -1)
//         return (127);
//     return (code);
// }

// int	main(int argc, char **av, char **envp)
// {
// 	(void)argc;
// 	char *path;

// 	path = find_path(av[1], envp, 0);
// 	printf("%s\n\n\n\n", path);
// 	// av++;
// 	// execve(path, ++av, envp);
// 	free(path);
// 	perror("");
// 	// if (path)
// 	// 	free(path);
// }