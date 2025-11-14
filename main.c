/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:19:22 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 11:19:23 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	exec_cmd(char *cmd_line, int input_fd, int output_fd, char **envp)
{
	char	**args;
	char	*cmd_path;

	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(input_fd);
	close(output_fd);
	args = ft_split(cmd_line, ' ');
	if (!args || !args[0])
		error_exit("invalid command");
	cmd_path = check_command(args, envp);
	if (!cmd_path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		write(2, "\n", 1);
		ft_free_split(args);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	free(cmd_path);
	ft_free_split(args);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
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
		child_first(pipex, fds, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork2");
	if (pid2 == 0)
		child_second(pipex, fds, argv, envp);
	close_all_parent(pipex, fds);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
