void	print_error(char *msg, char *cmd, int code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else
		ft_putchar_fd('\n', 2);
	exit(code);
}

char	*check_command(char **args, char **envp)
{
	char	*cmd_path;

	if (!args || !args[0])
		print_error("invalid command", NULL, 1);
	if (ft_strchr(args[0], '/'))
		cmd_path = ft_strdup(args[0]);
	else
		cmd_path = find_command(args[0], envp);
	if (!cmd_path)
		print_error("command not found", args[0], 127);
	if (access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		ft_free_split(args);
		print_error("permission denied", args[0], 126);
	}
	return (cmd_path);
}
