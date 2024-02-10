/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:21:44 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/10 18:14:11 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_handler(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Checks if a given command is in a given path
 * @param path A PATH's directory.
 * @returns -1 if path is NULL, 0 if the command isn't foud and 1 if it is.
 * If the command isn't found, the path's string is freed.
 */
static char	is_in_dir(char *path, char *in_dir)
{
	if (!path)
		return (*in_dir = -1, -1);
	if (!access(path, F_OK | X_OK))
		return (*in_dir = 1, 1);
	return (free(path), *in_dir = 0, 0);
}

/**
 * @brief Adds /"cmd" to one of PATH's directory.
 * @param dir A pointer to a string containing a PATH directory.
 * @param cmd The command to look for.
 * @returns The complete path containing the cmd, which will then be used
 * to check if the new path contains the executable of cmd.
 */
static char	*full_path(char *dir, char *cmd)
{
	char		*new;
	size_t		size;

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

//ajouter si path existe

/**
 * @brief Given an environment variable, finds the directory in which
 * the executable of the command is.
 * @param	env The environment variable.
 * @param	cmd The command to look for.
 * @param	i A variable used for incrementation.
 * @returns The path to the command's executable.
 */
char	*find_path(char **env, char *cmd, int i)
{
	char	**splited_path;
	char	*tmp_path;
	char	in_dir;

	if (!env || !cmd)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH", 4))
		i++;
	splited_path = ft_split(env[i], ':');
	if (!splited_path)
		perror("find_path !spl");
	i = 0;
	in_dir = 0;
	tmp_path = NULL;
	while (splited_path[i] && is_in_dir(tmp_path, &in_dir) != 1)
	{
		i++;
		tmp_path = full_path(splited_path[i], cmd);
		if (!tmp_path)
			return (free_arrs((void **) splited_path), perror("command not found"), NULL);
	}
	free_arrs((void **) splited_path);
	if (in_dir == 1)
		return (tmp_path);
	return (perror("command not found"), NULL);
}