/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:35:52 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/16 23:38:35 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_files
{
	int	infile;
	int	outfile;
}	t_files;

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	t_files	*fds;
	int		cmd_start;
}	t_pipex;

/*Main & Tools*/

void	child_second(int pipex[2], t_files fds, char **argv, char **envp);
void	child_first(int pipex[2], t_files fds, char **argv, char **envp);
int		open_reading(char *filename);
int		open_writing(char *filename);
void	close_all_parent(int pipex[2], t_files fds);
t_files	open_files(char **argv);
void	exec_cmd(char *cmd_line, int input_fd, int output_fd, char **envp);

/*LIBFT_tools*/

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/*Split*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(const char *s, char c);
int		subarray_count(const char *s, char c);
char	**fill_split(char **big, const char *s, int word_count, char c);
void	*free_split(char **big, int filled);

/* Error_handling*/

void	validacion_args(int argsc);
void	print_error(char *msg, char *cmd, int code);
char	*check_command(char **args, char **envp);
void	error_exit(char *sms);

/*Search_command*/

char	*find_command(char *cmd, char **envp);
void	ft_free_split(char **arr);

/*BONUS*/

void	validation_bonus_args(int argc);
t_files	open_bonus_files(int argc, char **argv);
int		make_bonus_child(char *cmd, int in, int out, char **envp);
void	exec_pipeloop(t_pipex *px);
void	wait_all_children(void);

/*Heredoc*/

int		is_here_doc(char **argv);
void	init_fds_and_mode(t_pipex *px, t_files *fds);
int		run_heredoc(char *limiter);

/*Get_next_line*/

char	*extract_line(char *rest);
char	*extract_rest(char *rest);
char	*add_rest(char *rest, char *buffer);
int		read_and_update_rest(int fd, char **rest);
char	*get_next_line(int fd);
size_t	ft_strlen_and_find_newline(const char *str, int *find_newline);

#endif