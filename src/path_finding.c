/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:30:57 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 12:48:26 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief CHecks if the PATH variable exists.
 * @param envp The environment variable.
 * @returns 0 if PATH isn't found, 1 otherwise.
 */
char	check_for_path(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Checks if a given command is in a given path
 * @param path A PATH's directory.
 * @returns -1 if path is NULL, 0 if the command isn't foud and 1 if it is.
 * If the command isn't found, the path's string is freed.
 */
static char	is_in_dir(char *path)
{
	if (!path)
		return (-1);
	if (!access(path, F_OK | X_OK))
		return (1);
	return (free(path), 0);
}

/**
 * @brief Checks if there is a '/'.
 * @param path A path to an executable.
 * @returns 1 if there is a '/' (we assume the given path is correct,
 * the execution won't work if it isn't, but it is handled.),
 * 0 if there is no '\'.
 */
static char	is_a_path(char *path)
{
	if (ft_strnstr(path, "/", ft_strlen(path)))
		return (1);
	return (0);
}

/**
 * @brief Joins a directory's path with a command.
 * @param dir A path to a directory.
 * @param cmd The command to look for.
 * @returns <dir>/<cmd>. NULL if there is no dir or no cmd,
 * or if the allocation failed.
 */
static char	*full_path(char *dir, char *cmd)
{
	char	*path;
	size_t	size;

	if (!dir || !cmd)
		return (NULL);
	size = ft_strlen(dir) + ft_strlen(cmd) + 1;
	path = (char *)ft_calloc(size + 2, sizeof(char));
	if (!path)
		return (NULL);
	ft_memcpy(path, dir, ft_strlen(dir));
	path[ft_strlen(dir)] = '/';
	ft_memcpy(path + ft_strlen(dir) + 1, cmd, ft_strlen(cmd));
	path[size] = '\0';
	return (path);
}

/**
 * @brief Finds the path of a given command, if it exists.
 * @param cmd The command for which to look for a path.
 * @param envp The environment varible.
 * @param i A variable used for incrementation.
 * @returns The path of a given command if it exists, if not,
 * error_handler is called.
 */
char	*find_path(char *cmd, char **envp, int i, t_process *dt)
{
	t_paths	utils;
	char	*s;

	utils.cmds = ft_split(cmd, ' ');
	if (!utils.cmds)
		return (dt->use_p = 0, error_handler(MKO, dt, 0), NULL);
	if (is_a_path(*utils.cmds) || !access(*utils.cmds, F_OK | X_OK))
		return (s = ft_strdup(*utils.cmds), free_arrs((void **)utils.cmds),
			f_env(envp, dt), s);
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	utils.all_paths = ft_split(*envp, ':');
	if (!utils.all_paths)
		return (dt->use_p = 0, error_handler(MKO, dt, 1, utils.cmds), NULL);
	utils.path = NULL;
	while (utils.all_paths[i] && is_in_dir(utils.path) != 1)
	{
		utils.path = full_path(utils.all_paths[i], utils.cmds[0]);
		if (!utils.path)
			return (dt->use_p = 0, error_handler(MKO, dt, 2, utils.all_paths,
					utils.cmds), NULL);
		i++;
	}
	return (free_multiple_arrs(2, utils.all_paths, utils.cmds), f_env(envp,
			dt), utils.path);
}
