/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:36 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/08 15:49:28 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	test(int *id)
// {
// 	*id = fork();
// 	printf("id in test is = %d\n", *id);
// }

// int	main(int ac, char **av, char **env)
// {
// 	int	id;
// 	char *args[] = {"cat", "test.c", NULL};
// 	(void)ac;
// 	test(&id);
// 	if (id == 0)
// 		printf("tg dans le process %d\n", id);
// 	else
// 		printf("tg dans le process %d\n", id);
// 	av++;
// 	printf("%s\n", *(env + 2));
// 	if (id == 0)
// 		execve("/bin/ls", av, NULL);
// 	else
// 		execve("/bin/cat", args, NULL);
// 	return (0);
// }

// int	main(void)
// {
// 	int	pipex[2];
// 	int	process_id;
// 	char	str[6];
//
// 	str[5] = 0;
// 	pipe(pipex);
// 	process_id = fork();
// 	if (process_id == 0)
// 	{
// 		close(pipex[0]);
// 		write(pipex[1], "salut", 5);
// 		close(pipex[1]);
// 	}
// 	else
// 	{
// 		read(pipex[0], str, 5);
// 		close(pipex[0]);
// 		close(pipex[1]);
// 	}
// }
//
// int	main(void)
// {
// 	int status;
// 	int	id;
// 	int	i;
//
// 	i = 0;
// 	status = 0;
// 	id = fork();
// 	printf("id = %d\n", id);
// 	if (id != 0)
// 		wait(&status);
// 	perror("");
// 	printf("status = %d\n", status);
// 	while (i < 10)
// 		printf("%d in process %d\n", i++, id);
// }

// int	main(int argc, char **av, char **env)
// {
// 	int	fd;
// 	int	process;

// 	(void)argc;
// 	av++;
// 	process = fork();
// 	if (process != 0)
// 	{
// 		fd = open("outfile", O_WRONLY);
// 		wait(&process);
// 		printf("process = %d\n", process);
// 		fd = dup2(fd, STDOUT_FILENO);
// 		execve("/bin/ls", av, env);
// 	}
// 	else
// 	{
// 		fd = open("infile", O_WRONLY);
// 		printf("fd process chuld %d\n", fd);
// 		fd = dup2(fd, STDOUT_FILENO);
// 		write(fd, "test depuis fd\n", 15);
// 		printf("fd process chuld %d\n", fd);
// 		write(STDOUT_FILENO, "test depuis stdout\n", 19);
// 		execve("/bin/ls", av, env);
// 	}
// }

// int	main(int ac, char **argv, char **env)
// {
// 	(void)ac;
// 	int fd;

// 	fd = 0;
// 	if (!access(argv[1], W_OK))
// 		fd = open(argv[1], O_WRONLY);
// 	printf("fd %d\n", fd);
// 	if (fd == -1)
// 		perror("Error");
// 		fd = dup2(fd, STDOUT_FILENO);
// 	if (execve("/bin/lseee", argv + 2, env) < 0)
// 		perror("");
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	char **cmd;
	char *path;
	int pid;
	int fd;
	int status;
	int pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid != 0)
	{
		wait(&status);
		cmd = cmd_array(av + 1);
		if (!cmd)
			return (1);
		path = find_path(env, cmd[0], 0);
		if (!path)
			return (1);
		printf("%s\n", path);
		fd = open("outfile", O_CREAT | O_EXCL | O_WRONLY);
		close(pipe_fd[1]);
		dup2(fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		execve(path, av + 1, env);
	}
	else
	{
		cmd = cmd_array(av + 1);
		if (!cmd)
			return (1);
		path = find_path(env, cmd[0], 0);
		if (!path)
			return (1);
		printf("%s\n", path);
		fd = open("infile", O_CREAT | O_EXCL | O_WRONLY);
		close(pipe_fd[0]);
		dup2(fd, STDOUT_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve(path, av + 1, env);
	}
}