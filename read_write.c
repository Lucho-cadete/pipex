/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:31:37 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/09 15:37:50 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_reading(char *filename)
{
	int	archivo_fd;

	archivo_fd = open(filename, O_RDONLY);
	if (archivo_fd == -1)
	{
		perror("Error by opening");
		exit (-1);
	}
	return (archivo_fd);
}

int	open_writing(char *filename)
{
	int	salida_fd;

	salida_fd = open (filename, O_CREAT | O_WRONLY, 0777);
	if (salida_fd == -1)
	{
		perror ("Error by writing");
		exit (-1);
	}
	return (salida_fd);
}
