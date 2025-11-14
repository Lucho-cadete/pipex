/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:31:37 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 10:48:05 by luimarti         ###   ########.fr       */
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

	salida_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (salida_fd == -1)
	{
		perror ("Error by writing");
		exit (-1);
	}
	return (salida_fd);
}

void	close_all_parent(int pipex[2], t_files fds)
{
	close(pipex[0]);
	close(pipex[1]);
	close(fds.infile);
	close(fds.outfile);
}

void	child_first(int pipex[2], t_files fds, char **argv, char **envp)
{
	close(pipex[0]);
	exec_cmd(argv[2], fds.infile, pipex[1], envp);
}

void	child_second(int pipex[2], t_files fds, char **argv, char **envp)
{
	close(pipex[1]);
	exec_cmd(argv[3], pipex[0], fds.outfile, envp);
}
