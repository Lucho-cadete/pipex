/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:59:52 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 16:52:24 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
