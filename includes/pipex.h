/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:58:35 by gcollet           #+#    #+#             */
/*   Updated: 2025/04/11 15:00:10 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define INVALID_ARGUMENT 0
# define PIPE_ERROR 1
# define FORK_ERROR 2
# define OPEN_FILE_ERROR 3
# define INVALID_PATH 4
# define EXECVE_ERROR 5
# define INVALID_INPUT 6

typedef struct s_pipex
{
	int		io[2];
	int		**fd;
	char	**path;
	int		argc;
	char	**argv;
	char	**envp;
}	t_pipex;

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp);
void	dup_fd(int **fd, int *io, int index, int argc);
void	error_handling(t_pipex data, int num);
void	open_files(t_pipex data, int io[2]);
void	close_fds(t_pipex data);
void	ft_free_matrix(char **arr);
int		**create_pipes(t_pipex data);
int		chechking_argument(char *str);
void	handle_child_process(t_pipex data, int index, char *cmd, char **spt);
void	pipex(t_pipex data);
char	*find_executable_path(t_pipex data, char *command);
char	**find_paths(char **envp);


// char	*find_executable_path(char *command, char **envp);

char	*get_next_line(int fd);
void	ft_get_line(int fd, char **line);
char	*ft_cut_str(char *line);
char	*future_next_line(char *line);

#endif
