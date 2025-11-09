/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:19:22 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/09 15:27:09 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *sms)
{
	perror(sms);
	exit(1);
}

t_files	open_files(char **argv)
{
	t_files	fds;

	fds.infile = open_reading(argv[1]);
	if (fds.infile < 0)
		error_exit("infile.txt");
	fds.outfile = open_writing(argv[4]);
	if (fds.outfile < 0)
		error_exit("outfile");
	return (fds);
}

void	exec_cmd1(int pipex[], char **argv, int infile_fd)
{
	char	comando[60];
	char	**args;

	dup2(infile_fd, STDIN_FILENO);
	dup2(pipex[1], STDOUT_FILENO);
	close(infile_fd);
	close(pipex[0]);
	close(pipex[1]);
	args = ft_split(argv[2], ' ');
	ft_strcpy(comando, "/bin/");
	ft_strcat(comando, args[0]);
	execve(comando, args, NULL);
	error_exit("execve cmd1");
}

void	exec_cmd2(int pipex[], char **argv, int outfile_fd)
{
	char	comando[60];
	char	**args;

	dup2(pipex[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(pipex[0]);
	close(pipex[1]);
	args = ft_split(argv[3], ' ');
	ft_strcpy(comando, "/bin/");
	ft_strcat(comando, args[0]);
	execve(comando, args, NULL);
	error_exit("execve cmd2");
}

int	main(int argc, char **argv)
{
	int		pipex[2];
	int		pid1;
	int		pid2;
	t_files	fds;

	validacion_args(argc);
	fds = open_files(argv);
	if (pipe(pipex) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");
	if (pid1 == 0)
		exec_cmd1(pipex, argv, fds.infile);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork2");
	if (pid2 == 0)
		exec_cmd2(pipex, argv, fds.outfile);
	close(pipex[0]);
	close(pipex[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
