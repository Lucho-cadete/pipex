/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:19:34 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/17 21:34:07 by lucho            ###   ########.fr       */
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

void	exec_pipeloop(t_pipex *px)
{
	int	prev;
	int	pipefd[2];
	int	i;

	prev = px->fds->infile;
	i = px->cmd_start;
	while (i < px->argc - 1)
	{
		if (i < px->argc - 2 && pipe(pipefd) == -1)
			error_exit("pipe");
		if (i == px->argc - 2)
			make_bonus_child(px->argv[i], prev, px->fds->outfile, px->envp);
		else
			make_bonus_child(px->argv[i], prev, pipefd[1], px->envp);
		close(prev);
		if (i < px->argc - 2)
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
	t_pipex	px;

	validation_bonus_args(argc);
	px.envp = envp;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		fds.infile = run_heredoc(argv[2]);
		fds.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		px.argv = argv + 1;
		px.argc = argc - 1;
		px.cmd_start = 2;
	}
	else
	{
		fds = open_bonus_files(argc, argv);
		px.argv = argv;
		px.argc = argc;
		px.cmd_start = 2;
	}
	px.fds = &fds;
	exec_pipeloop(&px);
	wait_all_children();
	return (0);
}
