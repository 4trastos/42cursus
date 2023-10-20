/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:49:21 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/20 21:15:16 by davgalle         ###   ########.fr       */
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
	size_t	i;
	void	*ptr;

	i = count * size;
	ptr = malloc(i);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, i);
	return (ptr);
}

char	*ft_read(int fd, char *buffer)
{
	int	bytes_read;
	char	frag[BUFFER_SIZE + 1];
	char	*new;

	*frag = *buffer;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, frag, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(frag);
			return (NULL);
		}
		frag[bytes_read] = 0;
		new = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!new)
			return (NULL);
		new = ft_strjoin(new, frag);
		return (new);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*line;
	char	*frag;
	char	*aux;
	int i;
	int dlen;
	int	bytes_read;

	aux = NULL;
	if (buffer)
	{
		aux = calloc(ft_strlen(buffer), sizeof(char));
		if (!aux)
			return (NULL);
		aux = buffer;
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0 , 0) < 0)
		return (NULL);
	buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
	buffer = ft_read(fd, buffer);
	bytes_read = ft_strlen(buffer);
	if (aux)
		buffer = ft_strjoin(aux, buffer);
	i = 0;
	if (buffer[0] == '\0')
		{
			line = NULL;
			return (line);
		}
	dlen = ft_strlen(buffer) + 1;
	line = calloc(dlen, sizeof(char));
	if (!line)
		return (NULL);
	while (i < dlen && buffer[i] != '\0')
	{
		if (buffer[i] == '\0')
		{
			free(line);
			line = NULL;
			line = get_next_line(fd);
		}
		if (buffer[i] == '\n' && buffer[i + 1] != '\0')
		{
			frag = calloc(dlen, sizeof(char));
			if (!frag)
				return (NULL);
			frag = ft_strchr(buffer, '\n');
			buffer = calloc(ft_strlen(frag), sizeof(char));
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
	line[i] = '\0';
	buffer = NULL;
	return (line);
}

/* int main(void)
{
	int fd = open("cancion.txt", O_RDONLY);
    char *line;

     while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
} */