/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_no_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:57:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 14:15:58 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*create_path(t_process *data)
{
	char	*path;
	char	*tmp;

	path = ft_strdup("PATH=/home/sokaraku/bin:/home/sokaraku/bin:");
	if (!path)
		return (data->use_p = 0, error_handler(MKO, data, 0), NULL);
	// tmp = path;
	// path = ft_strjoin(path, "/home/sokaraku/bin:/home/sokaraku/bin:");
	// free(tmp);
	// if (!path)
	// 	return (data->use_p = 0, error_handler(MKO, data, 0), NULL);
	tmp = path;
	path = ft_strjoin(path, "/usr/local/sbin:/usr/local/bin:");
	free(tmp);
	if (!path)
		return (data->use_p = 0, error_handler(MKO, data, 0), NULL);
	tmp = path;
	path = ft_strjoin(path, "/usr/sbin:/usr/bin:/sbin:/bin");
	free(tmp);
	if (!path)
		return (data->use_p = 0, error_handler(MKO, data, 0), NULL);
	return (path);
}
char	**reset_env(char **envp, t_process *data)
{
	char	*pseudo_path;

	pseudo_path = create_path(data);
	if (!pseudo_path)
	{
		data->use_p = 0;
		error_handler(MKO, data, 0);
	}
	printf("%s\n", pseudo_path);
	envp = ft_split(pseudo_path, ':');
	if (!envp)
	{
		free(pseudo_path);
		data->use_p = 0;
		error_handler(MKO, data, 0);
	}
	return (envp);
}

void	f_env(char **envp, t_process *data)
{
	if (data->env_modified == 1)
		if (data->env)
			free_arrs((void **)envp);
}