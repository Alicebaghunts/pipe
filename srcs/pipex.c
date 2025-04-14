/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-13 14:19:53 by alisharu          #+#    #+#             */
/*   Updated: 2025-04-13 14:19:53 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	run_command(t_pipex data, char *cmd, char **envp)
{
	char	**command;
	char	*path;

	if (chechking_argument(cmd) == 0)
		error_handling(data, 0);
	command = ft_split(cmd, ' ');
	path = find_executable_path(data, command[0]);
	if (!path)
	{
		ft_free_matrix(command);
		error_handling(data, 4);
	}
	if (execve(path, command, envp) == -1)
	{
		free(path);
		ft_free_matrix(command);
		error_handling(data, 5);
	}
}

void	first_child(t_pipex data)
{
	close(data.fd[0][0]);
	data.fd[1][0] = open(data.argv[1], O_RDONLY);
	if (data.fd[1][0] == -1)
		error_handling(data, 3);
	dup2(data.fd[1][0], STDIN_FILENO);
	dup2(data.fd[1][1], STDOUT_FILENO);
	close(data.fd[1][0]);
	close(data.fd[1][1]);
	run_command(data, data.argv[2], data.envp);
}

void	second_child(t_pipex data)
{
	close(data.fd[1][1]);
	data.fd[0][0] = open(data.argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.fd[0][0] == -1)
		error_handling(data, 3);
	dup2(data.fd[0][0], STDIN_FILENO);
	dup2(data.fd[0][1], STDOUT_FILENO);
	close(data.fd[0][0]);
	close(data.fd[0][1]);
	run_command(data, data.argv[3], data.envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	ft_memset(&data, 0, sizeof(t_pipex));
	if (argc < 5)
		error_handling(data, 6);
	init_pipex(&data, argc, argv, envp);
	if (argc > 6 && (strcmp("here_doc", argv[1]) == 0))
	{
		data.doc_flag = 1;
		here_doc(data);
	}
	else
		pipex(data);
	close_fds(data);
	while (wait(NULL) != -1)
		;
	ft_free_matrix(data.path);
	return (0);
}
