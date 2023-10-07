/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:35:17 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/07 22:07:28 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int	count_lines(fd)
{
	static int	i;
	char		buffer;
	ssize_t		bytes_read;

	if (i == 0)
	{
		i = 0;
		while ((bytes_read = read(fd, &buffer, 1)) > 0)
		{
			if (buffer == 0)
				i++;
		}
	}
	if (buffer != '\n' && i > 0)
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*new_line;
	char	buffer;
	int		i;
	ssize_t	bytes_read;

	line = NULL;
	i = 0;
	while ((bytes_read = read(fd, &buffer, 1)) > 0)
	{
		if (buffer == '\n')
			break ;
		new_line = realloc(line, i + 2);
		if (!new_line)
			return (NULL);
		line = new_line;
		line[i++] = buffer;
	}
	if (bytes_read == 0 && i == 0)
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

	fd = open("archivo.txt", O_RDONLY);

	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
	   free(line);	
	}
	close(fd);
	return (0);
}
