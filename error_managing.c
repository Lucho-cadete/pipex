/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:01:54 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/14 11:34:49 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validacion_args(int argsc)
{
	if (argsc != 5)
	{
		ft_putstr_fd("Invalid number of args\n", 2);
		exit(1);
	}
}

void	print_error(char *msg, char *cmd, int code)
{
	ft_putstr_fd(msg, 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	write (2, "\n", 1);
	exit(code);
}

char	*check_command(char **args, char **envp)
{
	char	*cmd_path;

	if (!args || !args[0] || args[0][0] == '\0')
		print_error("invalid command", NULL, 1);
	if (ft_strchr(args[0], '/'))
	{
		if (access(args[0], F_OK) != 0)
			print_error("command not found", args[0], 127);
		if (access(args[0], X_OK) != 0)
			print_error("permission denied", args[0], 126);
		return (ft_strdup(args[0]));
	}
	cmd_path = find_command(args[0], envp);
	if (!cmd_path)
		print_error("command not found", args[0], 127);
	return (cmd_path);
}

void	error_exit(char *sms)
{
	perror(sms);
	exit(1);
}
