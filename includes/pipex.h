/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:09:29 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 08:44:16 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ER_MALLOC "Allocation issue"

typedef struct s_paths
{
	char	*path;
	char	**all_paths;
	char	**cmds;
}			t_paths;

typedef struct s_process
{
	int		fd_in;
	int		fd_out;
	int		first_cmd;
	int		fds[2];
	pid_t	id;
	char	here_doc;
}			t_process;

void		free_multiple_arrs(int n, ...);
// void		error_handler(char *msg, t_process *data, int n, ...);
void		error_handler(char *msg, t_process *data, char use_p, int n, ...);
void		close_handler(int size, ...);
char		*find_path(char *cmd, char **envp, int i, t_process *data);
void		print_and_exit(char *msg);
void		pipex(int argc, char **argv, char **envp, t_process *data);
void		child(char *to_do, char **envp, char last, t_process *data);
void		ft_exec(char **envp, char *path, char **cmds);
void		check_and_open(int argc, char **argv, t_process *data);
void		here_doc(char *del, t_process *data, int argc, char **argv,
				char **envp);
void		test(char **argv, char **envp, t_process *data);
char		check_for_path(char **envp);

#endif