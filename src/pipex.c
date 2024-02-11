/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:25:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/11 14:00:15 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// check fds dans valgrnd

/**
 * @brief Prepare the arguments to launch the program. (file opening, forking)
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data A pointer to a structure containing multiple variables.
 * @returns void.
 */
static void	prepare_args(int argc, char **argv, t_process *data)
{
	data->fd_infile = open(argv[1], R_OK);
	if (data->fd_infile == -1)
		error_handler("");
	if (data->config == HERE_DOC)
		data->fd_outfile = open(argv[argc - 1], WR | TR | CR | AP, 0644);
	// bon 0644?
	else
		data->fd_outfile = open(argv[argc - 1], WR | TR | CR, 0644);
	if (data->fd_outfile == -1)
		error_handler("");
	if (data->config == MANDATORY)
	{
		if (pipe(data->fds) == -1)
			error_handler("");
		data->id = fork();
		if (data->id == -1)
			error_handler("");
	}
}

/**
 * @brief Checks if the arguments passed to the program are as expected.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data A pointer to a structure containing multiple variables.
 * @returns void.
 */
static void	check_args(int argc, char **argv, t_process *data)
{
	if (argc == 5)
		data->config = MANDATORY;
	else if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8))
		data->config = MULTIPLE_PIPES;
	else if (argc == 6)
		data->config = HERE_DOC;
	else
	{
		ft_putstr_fd("Expected arguments not found. Expected one of :\n", 2);
		ft_putstr_fd("infile cmd1 cmd2 outfile\n", 2);
		ft_putstr_fd("infile cmd1 cmd2 ... cmdn outfile\n", 2);
		ft_putstr_fd("here_doc LIMITER cmd cmd1 file\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	check_args(argc, argv, &data);
	prepare_args(argc, argv, &data);
	ft_exec(argc, argv, envp, &data);
	exit(EXIT_SUCCESS);
}
