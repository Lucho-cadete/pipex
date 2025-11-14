/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:19:34 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 16:52:20 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validation_bonus_args(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Uso: ./pipex infile cmd1 ... cmdN outfile\n", 2);
		exit(1);
	}
}

t_files	open_bonus_files(int argc, char **argv)
{
	t_files	fds;

	fds.infile = open_reading(argv[1]);
	fds.outfile = open_writing(argv[argc - 1]);
	if (fds.infile < 0 || fds.outfile < 0)
		error_exit("archivo");
	return (fds);
}

int	make_bonus_child(char *cmd, int in, int out, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
		exec_cmd(cmd, in, out, envp);
	return (pid);
}

void	exec_pipeloop(int argc, char **argv, char **envp, t_files *fds)
{
	int	prev;
	int	pipefd[2];
	int	i;

	prev = fds->infile;
	i = 2;
	while (i < argc - 1)
	{
		if (i < argc - 2 && pipe(pipefd) == -1)
			error_exit("pipe");
		if (i == argc - 2)
			make_bonus_child(argv[i], prev, fds->outfile, envp);
		else
			make_bonus_child(argv[i], prev, pipefd[1], envp);
		close(prev);
		if (i < argc - 2)
		{
			close(pipefd[1]);
			prev = pipefd[0];
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_files	fds;
	int		pid;
	int		finished;

	finished = 0;
	validation_bonus_args(argc);
	fds = open_bonus_files(argc, argv);
	exec_pipeloop(argc, argv, envp, &fds);
	while (!finished)
	{
		pid = waitpid(-1, NULL, 0);
		if (pid == -1)
			finished = 1;
	}
	return (0);
}
