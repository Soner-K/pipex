/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/16 18:52:36 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp, t_process *data)
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
			child(argv[i + 2], envp, i + 1 == (argc - 3), data);
		else
		{
			dup2(data->fds[0], STDIN_FILENO);
			close_handler(2, data->fds[0], data->fds[1]);
		}
		i++;
	}
}

void	child(char *to_do, char **envp, char last, t_process *data)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(to_do, ' ');
	path = find_path(*cmds, envp, 0);
	if (last == 0)
	{
		if (data->first_cmd == 0)
			if (dup2(data->fd_in, STDIN_FILENO) == -1)
				error_handler("dup2", data, 0);
		dup2(data->fds[0], data->fd_in);
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			error_handler("dup2", data, 0);
	}
	else
	{
		// dup2(data->fds[1], STDOUT_FILENO);
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			error_handler("dup2", data, 0);
	}
	data->first_cmd++;
	close_handler(4, data->fds[0], data->fds[1], data->fd_in, data->fd_out);
	ft_exec(envp, path, cmds);
}

//attention, close fd quand pas initialise ?

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

// dup2(data->fd_out, STDOUT_FILENO) pb car chaque exec ecrira dans le outfile?
// a voir quand la version sera complete
