/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:29:33 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 17:52:01 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen_and_find_newline(const char *str, int *find_newline)
{
	size_t	len;

	len = 0;
	*find_newline = 0;
	if (!str)
		return (0);
	while (str[len])
	{
		if (str[len] == '\n')
			*find_newline = 1;
		len++;
	}
	return (len);
}
