/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_coment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:35:17 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/08 15:14:03 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024 

char	*get_next_line(int fd)
{
	char	*line;
	char	*new_line;
	char	buffer;
	int		i;
	ssize_t	bytes_read;

	buffer = '\0';
	line = NULL;
	i = 0;
	while ((bytes_read = read(fd, &buffer, 1)) > 0)
	{
		if (buffer == '\n')
			break ;
		new_line = malloc(i + 2);
		if (!new_line)
			return (NULL);
		if (line)
        {
            memcpy(new_line, line, i);
            free(line);
        }
		line = new_line;
		line[i] = buffer;
		i++;
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
