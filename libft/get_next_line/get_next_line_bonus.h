/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:14:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/21 10:24:11 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	find_len(char const *s);
int		ft_check(char const *s, char c);
char	*ft_fuse(char *s1, char *s2);

char	*file_to_keep(int fd, char *keep, int *bytes_read);
char	*keep_to_line(char *keep);
char	*remove_from_keep(char *line, char *keep);
char	*get_next_line(int fd);
#endif