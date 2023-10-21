/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:34:19 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/21 19:15:41 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		return (0);
	}
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

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

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*j;
	size_t			i;

	j = s;
	i = 0;
	while (i < len)
	{
		j[i] = 0;
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		z;

	new = NULL;
	new = (char *)malloc(ft_strlen(s1) + ft_strlen (s2) +1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	z = i;
	i = 0;
	while (s2[i] != '\0')
	{
		new[z] = s2[i];
		z++;
		i++;
	}
	new[z] = '\0';
	return (new);
}

/* void	*ft_calloc(size_t count, size_t size)
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
} */
/* char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}	
	dest[i] = '\0';
	return (dest);
}
 */