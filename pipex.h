/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:35:52 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/09 15:34:56 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>

typedef struct s_files
{
	int	infile;
	int	outfile;
}	t_files;

/*Main*/

int		open_reading(char *filename);
int		open_writing(char *filename);
void	error_exit(char *sms);
t_files	open_files(char **argv);
void	exec_cmd1(int pipex[], char **argv, int infile_fd);
void	exec_cmd2(int pipex[], char **argv, int outfile_fd);
int		main(int argc, char **argv);
int		abre_lectura(char *filename);

/*Tools*/

void	validacion_args(int argsc);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
void	*ft_calloc(size_t nmemb, size_t size);

/*Split*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(const char *s, char c);
int		subarray_count(const char *s, char c);
char	**fill_split(char **big, const char *s, int word_count, char c);
void	*free_split(char **big, int filled);
