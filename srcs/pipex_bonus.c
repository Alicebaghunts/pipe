/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:34:39 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/15 01:53:57 by aadyan           ###   ########.fr       */
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
	open_files(*data, data->io);
	data->fd = create_pipes(*data);
	data->doc_flag = 0;
}

int	**create_pipes(t_pipex data)
{
	int	i;
	int	**pxik;

	i = 0;
	pxik = malloc(sizeof(int *) * (data.argc - 4));
	if (pxik == NULL)
		error_handling(data, 7);
	while (i < data.argc - 4)
	{
		pxik[i] = malloc(sizeof(int) * 2);
		if (pxik[i] == NULL)
			error_handling(data, 7);
		if (pipe(pxik[i]) == -1)
			error_handling(data, 1);
		i++;
	}
	return (pxik);
}

void	handle_child_process(t_pipex data, int index, char *cmd, char **splited)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_handling(data, 2);
	else if (pid == 0)
	{
		if (data.doc_flag == 1)
			dup_here_doc_fd(data.fd, data.io, index, data.argc);
		else
			dup_fd(data.fd, data.io, index, data.argc);
		close_fds(data);
		ft_free_matrix(data.path);
		execve(cmd, splited, data.envp);
		ft_free_matrix(splited);
		perror(cmd);
		free(cmd);
		exit(1);
	}
}

void	pipex(t_pipex data)
{
	int		index;
	char	*cmd;
	char	**splited;

	index = 1;
	while (++index != data.argc - 1)
	{
		if (chechking_argument(data.argv[index]) == 0)
			error_handling(data, 0);
		splited = ft_split(data.argv[index], ' ');
		cmd = find_executable_path(data, splited[0]);
		printf("%s\n", cmd);
		handle_child_process(data, index, cmd, splited);
		free(cmd);
		ft_free_matrix(splited);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	data;

// 	ft_memset(&data, 0, sizeof(t_pipex));
// 	if (argc < 5)
// 		error_handling(data, 6);
// 	init_pipex(&data, argc, argv, envp);
// 	pipex(data);
// 	close_fds(data);
// 	while (wait(NULL) != -1)
// 		;
// 	ft_free_matrix(data.path);
// 	return (0);
// }
