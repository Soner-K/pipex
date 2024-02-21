/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 08:44:55 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	access_all(char **argv, int argc)
// {
// 	int	i;

// 	i = 0;
// 	while (i < argc - 3)
// 	{
// 		if (access(argv[i]))
// 	}
// }

// gerer cas ou env unset mais deux script a executer ? 

//attention, close fd quand pas initialise ?
int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	if (argc != 5)
		print_exit("Wrong number of arguments");
	if (!envp[0])
		print_exit("Environment not found");
	if (check_for_path(envp) == 0)
		exit(EXIT_FAILURE);
	check_and_open(argc, argv, &data);
	pipex(argc, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
	exit(EXIT_SUCCESS);
}

// dup2(data->fd_out, STDOUT_FILENO) pb car chaque exec ecrira dans le outfile?
// a voir quand la version sera complete
