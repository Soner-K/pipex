/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:36 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/05 14:26:56 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	pipex[2];
	int	process_id;
	char	str[10];

	str[5] = 0;
	pipe(pipex);
	process_id = fork();
	if (process_id == 0)
	{
		close(pipex[0]);
		write(pipex[1], "salut", 5);
		close(pipex[1]);
	}
	else
	{
		read(pipex[0], str, 5);
		close(pipex[0]);
		close(pipex[1]);
	}
	printf("Process %d : string %s\n", process_id, str);
}
