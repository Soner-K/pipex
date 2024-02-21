/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 14:21:10 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_process *data, char **envp)
{
	data->fd_in = -1;
	data->fd_in = -1;
	data->fds[0] = -1;
	data->fds[1] = -1;
	data->first_cmd = 0;
	data->here_doc = -1;
	data->id = -1;
	data->use_p = 1;
	if (data->env_modified == 1)
		data->env = envp;
	else
		data->env = NULL;
}

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
	data.env_modified = 0;
	if (!check_for_path(envp))
	{
		envp = reset_env(envp, &data);
		if (!envp)
		{
			data.use_p = 0;
			error_handler(MKO, &data, 0);
		}
		data.env = envp;
		data.env_modified = 1;
	}
	init_struct(&data, envp);
	check_and_open(argc, argv, &data);
	pipex(argc, argv, envp, &data);
	while (wait(NULL) > 0)
		;
	close_handler(4, data.fd_in, data.fd_out, data.fds[0], data.fds[1]);
	exit(EXIT_SUCCESS);
}

// dup2(data->fd_out, STDOUT_FILENO) pb car chaque exec ecrira dans le outfile?
// a voir quand la version sera complete
