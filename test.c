/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:36 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/01 13:53:29 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	int	file_desc;
	int	copy_desc;

	// open() returns a file descriptor file_desc to a
	// the file "dup.txt" here"
	file_desc = open("dup.txt", O_WRONLY | O_APPEND | O_CREAT);
	if (file_desc < 0)
		printf("Error opening the file\n");
	// dup() will create the copy of file_desc as the copy_desc
	// then both can be used interchangeably.
	copy_desc = dup(file_desc);
	// write() will write the given string into the file
	// referred by the file descriptors
	write(copy_desc, "This will be output to the file named dup.txt\n", 46);
	write(file_desc, "This will also be output to the file named dup.txt\n",
		51);
	return (0);
}
