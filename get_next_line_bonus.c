/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:26:42 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/30 15:52:31 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_new_line(char *board)
{
	char	*new_line;

	if (!board)
		return (NULL);
	if (!ft_strchr(board, '\n'))
	{
		free(board);
		return (NULL);
	}
	new_line = ft_strchr(board, '\n');
	new_line = ft_strdup(new_line);
	free(board);
	return (new_line);
}

char	*ft_line(char *board)
{
	char	*ln;
	int		i;

	i = 0;
	if (!board[i])
		return (NULL);
	if (!ft_strchr(board, '\n'))
		ln = ft_strdup(board);
	else
	{
		ln = malloc(ft_strchr(board, '\n') - board + 1);
		if (!ln)
			return (NULL);
		while (board[i] != '\n')
		{
			ln[i] = board[i];
			i++;
		}
		ln[i] = board[i];
		ln[i + 1] = '\0';
	}
	return (ln);
}

char	*ft_read(int fd, char *board)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(board);
		return (NULL);
	}
	bytes_read = 1;
	while (board && !ft_strchr(board, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(board);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		board = ft_strjoin(board, buffer);
	}
	free(buffer);
	return (board);
}

char	*get_next_line(int fd)
{
	static char	*board[1300];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!board[fd])
	{
		board[fd] = malloc(1);
		if (!board[fd])
			return (NULL);
		*board[fd] = '\0';
	}
	board[fd] = ft_read(fd, board[fd]);
	if (!board[fd])
		return (NULL);
	line = ft_line(board[fd]);
	board[fd] = ft_new_line(board[fd]);
	return (line);
}

/* int main(void)
{	
	const char *files[] = {"read_error.txt", "giant_line.txt", "el_quijote.txt"};

	int i = 0;
	while (i < sizeof(files) / sizeof(files[0]))
	{
		int fd = open(files[i], O_RDONLY);
    	if (fd < 0)
		{
      		perror("open");
      		return 1;
    	}

    	char *line;
    	while ((line = get_next_line(fd)) != NULL)
		{
      		printf("%s", line);
      		free(line);
    	}
    	close(fd);
		i++;
	}
} */