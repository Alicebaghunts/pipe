/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:42:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/15 02:00:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_handling(t_pipex data, int num)
{
	if (num == 0)
		ft_putstr_fd("❌ \033[31mError: Invalid argument\e[0m\n", 2);
	else if (num == 1)
		ft_putstr_fd("❌ \033[31mError: Failed to create pipe\e[0m\n", 2);
	else if (num == 2)
		ft_putstr_fd("❌ \033[31mError: Failed to create child\e[0m\n", 2);
	else if (num == 3)
		ft_putstr_fd("❌ \033[31mError: Failed to open file\e[0m\n", 2);
	else if (num == 4)
		ft_putstr_fd("❌ \033[31mError: Invalid path\e[0m\n", 2);
	else if (num == 5)
		ft_putstr_fd("❌ \033[31mError: Failed to run command\e[0m\n", 2);
	else if (num == 6)
		ft_putstr_fd("❌ \033[31mError: Invslid input\e[0m\n", 2);
	else if (num == 7)
		ft_putstr_fd("❌ \033[31mError: Malloc failed\e[0m\n", 2);
	close_fds(data);
	if (data.path)
		ft_free_matrix(data.path);
	exit(num);
}

void	close_fds(t_pipex data)
{
	int	i;

	i = 0;
	if (data.fd)
	{
		while (i != data.argc - 4)
		{
			close(data.fd[i][0]);
			close(data.fd[i][1]);
			free(data.fd[i]);
			i++;
		}
		free(data.fd);
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

void	ft_free_matrix(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
