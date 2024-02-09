/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:21:56 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/09 15:51:52 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// pb --> 2 cmd en un tab, comment gerer ca avec execve?
// incrementer pointeur? stocker adresse puis mettre a null a separateur?
// les erreurs affichent success gros regle ca vite
// char	**cmd_array(char **av)
// {
// 	char	**cmd;
// 	char	*str;
// 	char	*to_del;

// 	str = ft_strjoin(av[2], " SEPARATOR ");
// 	if (!str)
// 		ft_error("Issue in cmd_array (ft_strjoin)");
// 	to_del = str;
// 	str = ft_strjoin(str, av[3]);
// 	free(to_del);
// 	if (!str)
// 		ft_error("Issue in cmd_array (ft_strjoin)");
// 	cmd = ft_split(str, ' ');
// 	if (!cmd)
// 		ft_error("Issue in cmd_array (ft_split)");
// 	free(str);
// 	for (int i = 0; cmd[i]; i++)
// 		printf("|%s|\n", cmd[i]);
// 	return (cmd);
// }


// char	**cmd_array(char **av, int *next_cmd)
// {
// 	char	**cmd;
// 	char	*str;
// 	char	*to_del;

// 	*next_cmd = 0;
// 	str = ft_strjoin(av[1], " SEPARATOR ");
// 	if (!str)
// 		ft_error("Issue in cmd_array (ft_strjoin)");
// 	to_del = str;
// 	str = ft_strjoin(str, av[2]);
// 	free(to_del);
// 	if (!str)
// 		ft_error("Issue in cmd_array (ft_strjoin)");
// 	cmd = ft_split(str, ' ');
// 	if (!cmd)
// 		ft_error("Issue in cmd_array (ft_split)");
// 	free(str);
// 	while (cmd[*next_cmd] && ft_strncmp(cmd[*next_cmd], "SEPARATOR", 9))
// 		(*next_cmd)++;
// 	for (int i = 0; cmd[i]; i++)
// 		printf("||%s||\n", cmd[i]);
// 	return (cmd);
// }

void	child(char **cmds, char **env, int fds[])
{
	char	*path;

	path = find_path(env, cmds[0], 0);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	if (execve(path, cmds, env) == 1)
		perror("child");
}

void	parent(char **cmds, char **env, int fds[])
{
	char	*path;

	path = find_path(env, cmds[0], 0);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	if (execve(path, cmds, env) == -1)
		perror("parent");
}

// int	main(int ac, char **av, char **env)
// {
// 	char	**cmds;
// 	int		fds[2];
// 	int		id;
// 	int		i;

// 	(void)ac;
// 	cmds = cmd_array(av, &i);
// 	if (pipe(fds) == -1)
// 		return (1);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		cmds[i] = NULL;
// 		child(cmds, env, fds);
// 	}
// 	wait(NULL);
// 	cmds += i + 1;
// 	parent(cmds, env, fds);
// }

// int	main(int ac, char **av)
// {
// 	char **cmd;
// 	int	i;

// 	i = 0;
// 	if (ac == 5)
// 		cmd = cmd_array(av);
// 	else
// 		return (printf("Wrong nomber connard de merde\n"), 1);
// 	while (cmd[i])
// 		printf("||%s||\n", cmd[i++]);
// 	free_arrs((void **) cmd);
// }