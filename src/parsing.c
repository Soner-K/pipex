/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:21:56 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/08 15:19:36 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//pb --> 2 cmd en un tab, comment gerer ca avec execve?
//incrementer pointeur? stocker adresse puis mettre a null a separateur?
//les erreurs affichent success gros regle ca vite
char	**cmd_array(char **av)
{
	char	**cmd;
	char	*str;
	char	*to_del;

	str = ft_strjoin(av[2], " SEPARATOR ");
	if (!str)
		ft_error("Issue in cmd_array (ft_strjoin)");
	to_del = str;
	str = ft_strjoin(str, av[3]);
	free(to_del);
	if (!str)
		ft_error("Issue in cmd_array (ft_strjoin)");
	cmd = ft_split(str, ' ');
	if (!cmd)
		ft_error("Issue in cmd_array (ft_split)");
	free(str);
	return (cmd);
}


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