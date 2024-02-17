/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/17 18:11:00 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//attention, close fd quand pas initialise ?
int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	if (argc != 5)
		print_and_exit("Wrong number of arguments");
	if (!envp[0])
		print_and_exit("Environment not found");
	check_and_open(argc, argv, &data);
	pipex(argc, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
}

// dup2(data->fd_out, STDOUT_FILENO) pb car chaque exec ecrira dans le outfile?
// a voir quand la version sera complete
