/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:49:21 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/21 21:28:32 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_read(int fd, char *buffer)
{
	int		bytes_read;
	char	frag[BUFFER_SIZE + 1];
	char	*new;

	new = NULL;
	bytes_read = read(fd, frag, BUFFER_SIZE);
	if (bytes_read > 0)
		frag[bytes_read] = '\0';
	if (bytes_read <= 0)
	{
		if (buffer)
			return (buffer);
		return (NULL);
	}
	else
	{
		new = ft_strjoin(buffer, frag);
		return (new);
	}
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;
	char			*frag;
	char			*aux;
	unsigned long	i;

	aux = NULL;
	if (buffer)
	{
		aux = ft_calloc(ft_strlen(buffer), sizeof(char));
		if (!aux)
			return (NULL);
		aux = buffer;
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (aux)
		buffer = ft_strjoin(aux, buffer);
	i = 0;
	if (buffer[0] == '\0')
		return (line = NULL);
	line = ft_calloc((ft_strlen(buffer) + 1), sizeof(char));
	if (!line)
		return (NULL);
	while (i < ft_strlen(buffer) + 1 && buffer[i] != '\0')
	{
		if (buffer[i] == '\0')
		{
			free(line);
			line = get_next_line(fd);
		}
		if (buffer[i] == '\n' && buffer[i + 1] != '\0')
		{
			frag = ft_calloc(ft_strlen(buffer) + 1, sizeof(char));
			if (!frag)
				return (NULL);
			frag = ft_strchr(buffer, '\n');
			buffer = ft_calloc(ft_strlen(frag), sizeof(char));
			if (!buffer)
				return (NULL);
			buffer = frag;
			line[i] = '\n';
			return (line);
		}
		if (buffer[i] == '\n' && buffer[i + 1] == '\0')
		{
			line[i] = buffer[i];
			buffer = NULL;
			aux = NULL;
			return (line);
		}
		line[i] = buffer[i];
		i++;
	}
	buffer = NULL;
	return (line);
}
/*
int main(void)
{
	int fd = open("read_error.txt", O_RDONLY);
    char *line;

     while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}*/
