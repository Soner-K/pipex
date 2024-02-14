/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:09:29 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/14 12:41:16 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_paths
{
	char	*path;
	char	**all_paths;
	char	**cmds;
}			t_paths;

void		free_multiple_arrs(int n, ...);
void		error_handler(char *msg, int n, ...);
void		close_handler(int size, ...);
char		*find_path(char *cmd, char **envp, int i);


#endif