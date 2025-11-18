/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:34:04 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/18 17:46:51 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (1);
	return (0);
}

void	init_fds_and_mode(t_pipex *px, t_files *fds)
{
	if (is_here_doc(px->argv))
	{
		fds->infile = run_heredoc(px->argv[2]);
		fds->outfile = open(px->argv[px->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		px->cmd_start = 3;
	}
	else
	{
		*fds = open_bonus_files(px->argc, px->argv);
		px->cmd_start = 2;
	}
	px->fds = fds;
}

int	run_heredoc(char *limiter)
{
	int		fd[2];
	char	*line;
	int		lim_len;

	if (pipe(fd) == -1)
		error_exit("pipe");
	lim_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, lim_len) && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
