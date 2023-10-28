/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:26:42 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/28 12:18:24 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_line(char *board)
{
	char	*new_line;

	if (!ft_strchr(board, '\n'))
	{
		free(board);
		return (NULL);
	}
	if (!board)
		return (NULL);
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
	ln = malloc(ft_strlen(board) + 2);
	if (!ln)
		return (NULL);
	while (board[i] && board[i] != '\n')
	{
		ln[i] = board[i];
		i++;
	}
	if (board[i] == '\n')
	{
		ln[i] = board[i];
		ln[i +1] = '\0';
	}
	else
	{
		free(ln);
		ln = ft_strdup(board);
	}
	return (ln);
}

char	*ft_read(int fd, char *board)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(board);
			return (NULL);
		}
		if (bytes_read == 0)
			return (board);
		buffer[bytes_read] = '\0';
		board = ft_strjoin(board, buffer);
		if (ft_strchr(board, '\n'))
			break ;
	}
	return (board);
}

char	*get_next_line(int fd)
{
	static char	*board;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	board = ft_read(fd, board);
	if (!board)
		return (NULL);
	line = ft_line(board);
	board = ft_new_line(board);
	return (line);
}
/* int main(void)
{
	int fd = open("1char.txt", O_RDONLY);
    char *line;

     while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
} */
