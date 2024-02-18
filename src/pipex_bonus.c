/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:35:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/18 21:53:39 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex2(int argc, char **argv, char **envp, t_process *data)
{
	int	i;

	i = 0;
	data->first_cmd = 0;
	while (i < argc - 3)
	{
		if (pipe(data->fds) == -1)
			error_handler("pipe", data, 0);
		data->id = fork();
		if (data->id == -1)
			error_handler("fork", data, 0);
		if (data->id == 0)
			child(argv[i + 3], envp, i + 1 == (argc - 3), data);
		else
		{
			dup2(data->fds[0], STDIN_FILENO);
			close_handler(2, data->fds[0], data->fds[1]);
		}
		i++;
		data->first_cmd++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_process	data;

	if (argc < 5)
		print_and_exit("Wrong number of arguments");
	if (!envp[0])
		print_and_exit("Environment not found");
	check_and_open(argc, argv, &data);
	if (data.here_doc == 1)
		here_doc(argv[2], &data, argc, argv, envp);
	else
		pipex2(argc - 1, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
}
