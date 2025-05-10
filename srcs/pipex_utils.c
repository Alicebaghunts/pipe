/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:03:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/18 20:48:01 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdlib.h>

void	error_handling(t_pipex *data, int num)
{
	if (num == 1)
		ft_putstr_fd("❌ \033[31mError: Failed to create pipe\e[0m\n", 2);
	else if (num == 2)
		ft_putstr_fd("❌ \033[31mError: Failed to create child\e[0m\n", 2);
	else if (num == 3)
		ft_putstr_fd("❌ \033[31mError: Failed to open file\e[0m\n", 2);
	else if (num == 4)
		ft_putstr_fd("❌ \033[31mError: Invalid argument\e[0m\n", 2);
	else if (num == 5)
		ft_putstr_fd("❌ \033[31mError: Failed to run command\e[0m\n", 2);
	else if (num == 6)
		ft_putstr_fd("❌ \033[31mError: Invalid input\e[0m\n", 2);
	else if (num == 7)
		ft_putstr_fd("❌ \033[31mError: Malloc failed\e[0m\n", 2);
	else if (num == 8)
		ft_putstr_fd("❌ \033[31mError: Command not found\e[0m\n", 2);
	close_fds(data);
	if (data->path)
		ft_free_matrix(&data->path);
	if (data)
		free(data);
	exit(num);
}

void	close_fds(t_pipex *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		while (i != data->argc - 4)
		{
			close(data->fd[i][0]);
			close(data->fd[i][1]);
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
		data->fd = NULL;
	}
}

void	close_io(int *io)
{
	if (io[0] != -1)
		close(io[0]);
	if (io[1] != -1)
		close(io[1]);
}

int	chechking_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	ft_free_matrix(char ***arr)
{
	int	i;

	i = 0;
	if (!*arr)
		return ;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}
