/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:03:40 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/17 14:06:48 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_here_doc_fd(int **fd, int *io, int index, int argc)
{
	if (index == 3)
	{
		dup2(fd[0][0], STDIN_FILENO);
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

void	open_here_doc(t_pipex *data)
{
	char	*str;
	char	*lim;

	lim = ft_strjoin(data->argv[2], "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str || ft_strcmp(str, lim) == 0)
			break ;
		ft_putstr_fd(str, data->fd[0][1]);
		free(str);
	}
	free(lim);
	free(str);
}

void	here_doc(t_pipex *data)
{
	int		index;
	char	*cmd;
	char	**splited;

	index = 2;
	open_here_doc(data);
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
		ft_free_matrix(&splited);
	}
}
