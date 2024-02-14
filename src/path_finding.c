/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:30:57 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/14 12:40:26 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	is_in_dir(char *path)
{
	if (!path)
		return (-1);
	if (!access(path, F_OK | X_OK))
		return (1);
	return (free(path), 0);
}

static char	is_a_path(char *cmd)
{
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (1);
	return (0);
}

static char	*full_path(char *dir, char *cmd)
{
	char	*new;
	size_t	size;

	if (!dir || !cmd)
		return (NULL);
	size = ft_strlen(dir) + ft_strlen(cmd) + 1;
	new = (char *)ft_calloc(size + 2, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, dir, ft_strlen(dir));
	new[ft_strlen(dir)] = '/';
	ft_memcpy(new + ft_strlen(dir) + 1, cmd, ft_strlen(cmd));
	new[size] = '\0';
	return (new);
}

char	*find_path(char *cmd, char **envp, int i)
{
	t_paths	utils;

	if (!cmd || !envp)
		return (NULL);
	if (is_a_path(cmd) || !access(cmd, F_OK | X_OK))
		return (cmd);
	utils.cmds = ft_split(cmd, ' ');
	if (!utils.cmds)
		error_handler("Allocation failed", 0);
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	while (*envp && (**envp) != '/')
		(*envp)++;
	utils.all_paths = ft_split(*envp, ':');
	if (!utils.all_paths)
		error_handler("Allocation failed", 1, utils.cmds);
	utils.path = NULL;
	while (utils.all_paths[i] && is_in_dir(utils.path) != 1)
	{
		utils.path = full_path(utils.all_paths[i], utils.cmds[0]);
		if (!utils.path)
			error_handler("Allocation failed", 2, utils.all_paths, utils.cmds);
		i++;
	}
	return (free_multiple_arrs(2, utils.all_paths, utils.cmds), utils.path);
}