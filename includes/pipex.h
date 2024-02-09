/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:51 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/09 15:37:44 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_process
{
	int		fds[2];
	int		fd_infile;
	int		fd_outfile;
	pid_t	id;
}			t_process;

typedef struct s_path
{
	char	*path;
	char	**cmds;
}			t_path;

void ft_error(char *str);
char		*find_path(char **env, char *cmd, int i);
char		**cmd_array(char **av, int *next_cmd);

#endif