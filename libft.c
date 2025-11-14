/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:11:39 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 10:47:56 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_strcat(char *dest, char *src)
{
	char	*beginning;

	beginning = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (beginning);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	tmp = malloc (nmemb * size);
	i = 0;
	if (!tmp)
		return (NULL);
	while (i < nmemb * size)
		tmp [i++] = 0;
	return (tmp);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	stop;

	stop = 0;
	while (stop < n)
	{
		if ((unsigned char)s1[stop] != (unsigned char)s2[stop])
		{
			return ((unsigned char)s1[stop] - (unsigned char)s2[stop]);
		}
		if ((unsigned char)s1[stop] == '\0')
		{
			return (0);
		}
		stop++;
	}
	return (0);
}
