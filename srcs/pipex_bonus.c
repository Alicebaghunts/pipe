/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:49:08 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/17 14:12:35 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_fd(int **fd, int *io, int index, int argc)
{
	if (index == 2)
	{
		dup2(io[0], STDIN_FILENO);
		dup2(fd[index - 2][1], STDOUT_FILENO);
	}
	else if (index == argc - 2)
	{
		dup2(fd[index - 3][0], STDIN_FILENO);
		dup2(io[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd[index - 3][0], STDIN_FILENO);
		dup2(fd[index - 2][1], STDOUT_FILENO);
	}
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->path = find_paths(envp);
	open_files(data, data->io);
	data->fd = create_pipes(data);
	data->doc_flag = 0;
}

int	**create_pipes(t_pipex *data)
{
	int	i;
	int	**pxik;

	i = 0;
	pxik = malloc(sizeof(int *) * (data->argc - 4));
	if (pxik == NULL)
		error_handling(data, MALLOC_ERROR);
	while (i < data->argc - 4)
	{
		pxik[i] = malloc(sizeof(int) * 2);
		if (pxik[i] == NULL)
			error_handling(data, MALLOC_ERROR);
		if (pipe(pxik[i]) == -1)
			error_handling(data, PIPE_ERROR);
		i++;
	}
	return (pxik);
}

void	handle_child_process(t_pipex *data, int index, char *cmd, char **splt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_handling(data, FORK_ERROR);
	else if (pid == 0)
	{
		if (data->doc_flag == 1)
			dup_here_doc_fd(data->fd, data->io, index, data->argc);
		else
			dup_fd(data->fd, data->io, index, data->argc);
		close_fds(data);
		ft_free_matrix(data->path);
		data->path = NULL;
		if (execve(cmd, splt, data->envp) == -1)
		{
			ft_free_matrix(splt);
			free(cmd);
			close_io(data->io);
			error_handling(data, INVALID_COMMAND);
		}
	}
}

void	pipex(t_pipex *data)
{
	int		index;
	char	*cmd;
	char	**splited;

	index = 1;
	while (++index != data->argc - 1)
	{
		if (chechking_argument(data->argv[index]) == 0)
		{
			close_io(data->io);
			error_handling(data, INVALID_ARGUMENT);
		}
		splited = ft_split(data->argv[index], ' ');
		cmd = find_executable_path(data, splited[0]);
		handle_child_process(data, index, cmd, splited);
		free(cmd);
		ft_free_matrix(splited);
	}
}
