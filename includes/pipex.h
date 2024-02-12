/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:51 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/12 16:28:09 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MANDATORY 0
# define MULTIPLE_PIPES 1
# define HERE_DOC 2

# define WR O_WRONLY
# define R_W O_RDWR
# define TR O_TRUNC
# define CR O_CREAT
# define AP O_APPEND

typedef struct s_process
{
	int		fds[2];
	int		fd_in;
	int		fd_out;
	int		*info_id;
	pid_t	id;
	char	config;
}			t_process;

typedef struct s_path
{
	char	*path;
	char	**cmds;
}			t_path;

void		error_handler(char *msg);
char		*find_path(char **env, char *cmd, int i);
void		ft_exec(int argc, char **argv, char **envp, t_process *data);
void		close_handler(int size, ...);
char		exec_one(char *cmd, char **envp, t_process *data);
void		pipe_here_doc(int argc, char **argv, char **envp, t_process *data);
void		files_handler(t_process *dt);

#endif