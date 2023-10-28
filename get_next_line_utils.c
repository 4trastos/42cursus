/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:34:19 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/28 12:16:40 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
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
	size_t	j;
	char	*str;

	if (!board)
	{
		board = malloc(1);
		if (!board)
			return (NULL);
		board[0] = '\0';
	}
	if (!board || !buffer)
		return (NULL);
	str = malloc((ft_strlen(board) + ft_strlen(buffer) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (board[++i] != '\0')
			str[i] = board[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[i++] = '\0';
	free(board);
	return (str);
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