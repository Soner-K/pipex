/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:35:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 18:04:05 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	if (argc < 5)
		print_exit("Wrong number of arguments");
	if (!envp || !envp[0] || !check_for_path(envp))
		print_exit("Environment not found");
	check_and_open(argc, argv, &data);
	data.use_p = 1;
	if (data.here_doc == 1)
		here_doc(argv, envp, &data);
	else
		pipex(argc, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
}
