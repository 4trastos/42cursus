/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:34:19 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/28 19:08:49 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i] + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *board, char *buffer)
{
	size_t	i;
	size_t	z;
	char	*board_dir;

	if (ft_strlen(buffer) == 0)
		return (board);
	board_dir = malloc((ft_strlen(board) + ft_strlen(buffer) + 1));
	if (!board_dir)
	{
		free(board);
		return (NULL);
	}
	i = -1;
	while (board[++i] != '\0')
		board_dir[i] = board[i];
	z = 0;
	while (buffer[z] != '\0')
		board_dir[i++] = buffer[z++];
	board_dir[i] = '\0';
	free(board);
	return (board_dir);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/* char	*ft_new_line(char *board)
{
	int		i;
	int		j;
	char	*new_line;

	if (!board)
		return (NULL);
	if (!ft_strchr(board, '\n'))
	{
		free(board);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (board[i] && board[i] != '\n')
		i++;
	new_line = malloc(ft_strlen(board) - i + 1);
	if (!new_line)
		return (NULL);
	i++;
	while (board[i])
		new_line[j++] = board[i++];
	new_line[j] = '\0';
	free(board);
	return (new_line);
} */

/* char	*ft_read(int fd, char *board)
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
} */
/* char	*ft_line(char *board)
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
		i++;
	}
	else
	{
		free(ln);
		ln = ft_strdup(board);
		return (ln);
	}
	ln[i] = '\0';
	return (ln);
} */
/* char	*ft_new_line(char *board)
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
} */
