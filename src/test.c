/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:36 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/09 12:42:03 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

// int	main(int ac, char **av)
// {
// 	(void) ac;
// 	(void) av;
// 	int		fds[2];
// 	int		id;

// 	if (pipe(fds) == -1)
// 		perror("");
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fds[0]);
// 		write(fds[1], "ouais", 5);
// 		close(fds[1]);
// 	}
// 	else
// 	{
// 		// wait(NULL);
// 		close(fds[1]);
// 		char str[6];
// 		str[5] = 0;
// 		read(fds[0], str, 5);
// 		printf("%s\n", str);
// 		close(fds[0]);
// 	}
// 	return (0);
// }

// erreur sur fork?
// int	main(void)
// {
// 	int fds[2];
// 	int id;
// 	int tab[] = {1, 1, 1, 1, 2, 22, 222, 2222, 22222, 222222, 2222222, 22222222,
// 		2222222, 222222, 22222, 2222, 222, 22, 2};
// 	int i;
// 	int arr_size;
// 	int even_number;

// 	arr_size = sizeof(tab) / sizeof(int);
// 	if (pipe(fds) == -1)
// 		perror("");
// 	i = 0;
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fds[0]);
// 		dup2(fds[1], STDOUT_FILENO);
// 		while (arr_size--)
// 		{
// 			if (!(tab[i] % 2))
// 				printf("%d ", tab[i]);
// 			i++;
// 		}
// 		close(fds[1]);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(fds[1]);
// 		dup2(fds[0], STDIN_FILENO);
// 		while (scanf("%d", &even_number) != EOF)
// 			printf("%d\n", even_number);
// 		close(fds[0]);
// 	}
// 	return (1);
// }

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	int fds[2];
// 	int id;
// 	char **cmds;
// 	char	*av2[1];
// 	char *path;

// 	cmds = cmd_array(av);
// 	if (!cmds)
// 		exit(1);
// 	if (pipe(fds) == -1)
// 		return (-1);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		path = find_path(env, cmds[0], 0);
// 		printf("child %s\npath %s\n", cmds[0], path);
// 		close(fds[0]);
// 		dup2(fds[1], STDOUT_FILENO);
// 		av2[0] = cmds[0];
// 		av++;
// 		execve("/bin/ls", av, env);
// 		return (1);
// 	}
// 	else
// 	{
// 		path = find_path(env, cmds[2], 0);
// 		printf("parent %s\n", cmds[2]);
// 		close(fds[1]);
// 		dup2(fds[0], STDIN_FILENO);
// 		av2[0] = cmds[2];
// 		execve(path, av2, env);
// 		return (1);
// 	}
// }