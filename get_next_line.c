/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:35:17 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/10 15:29:52 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd)
{
	char	*line;
	char	*new_line;
	char	buffer;
	int		i;
	ssize_t	bytes_read;
	ssize_t	buffer_size;

	buffer_size = BUFFER_SIZE;
	line = malloc(buffer_size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (1)
	{
		bytes_read = read(fd, &buffer, 1);
		if (bytes_read > 0)
		{
			if (i == buffer_size - 1)
			{
			buffer_size = buffer_size + BUFFER_SIZE;
			new_line = (char *)malloc(buffer_size);
				if (!new_line)
				{
					free(line);
					return (NULL);
				}
				memcpy(new_line, line, i);
				free(line);
				line = new_line;
			}
			line[i] = buffer;
			i++;
			if (buffer == '\n')
			{
				break ;
			}
		}
		else if (bytes_read <= 0)
		{
			break ;
		}
	}
	if (bytes_read < 0 || (bytes_read == 0 && i == 0))
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("get_next_line.c", O_RDONLY);

	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
