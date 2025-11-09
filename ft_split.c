/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:16:19 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/09 15:21:01 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

char	**ft_split(const char *s, char c)
{
	char		**big;
	int			word_count;

	if (!s)
		return (NULL);
	word_count = subarray_count (s, c);
	big = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!big)
		return (NULL);
	return (fill_split(big, s, word_count, c));
}

int	subarray_count(const char *s, char c)
{
	int	i;
	int	trigger;
	int	count;

	i = 0;
	trigger = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (count);
}

char	**fill_split(char **big, const char *s, int word_count, char c)
{
	const char	*str;
	int			i;
	int			len;

	i = 0;
	while (*s && i < word_count)
	{
		while (*s == c)
			s++;
		len = 0;
		str = s;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		big[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!big[i])
			return (free_split(big, i));
		ft_strlcpy (big[i], str, len + 1);
		i++;
	}
	big[i] = NULL;
	return (big);
}

void	*free_split(char **big, int filled)
{
	int	i;

	i = 0;
	while (i < filled)
	{
		free(big[i]);
		i++;
	}
	free(big);
	return (NULL);
}
