/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:35:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/17 19:02:27 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	if (argc < 5)
		print_and_exit("Wrong number of arguments");
	if (!envp[0])
		print_and_exit("Environment not found");
	check_and_open(argc, argv, &data);
	if (data.here_doc == 0)
		here_doc(argv[2], &data, argc, argv, envp);
	else
		pipex(argc, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
}
