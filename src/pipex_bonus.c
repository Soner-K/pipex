/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:35:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/16 19:35:23 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	if (argc != 5)
		print_and_exit("Wrong number of arguments");
	if (!envp[0])
		print_and_exit("Environment not found");
	data.fd_in = open(argv[1], O_RDONLY);
	if (data.fd_in == -1)
		print_and_exit("Failed to open infile");
	data.fd_out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data.fd_out == -1)
	{
		printf("sdsdsdsdsd\n");
		close(data.fd_in);
		print_and_exit("Failed to open outfile");
	}
	pipex(argc, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
}
