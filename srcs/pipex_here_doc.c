/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-13 15:11:00 by alisharu          #+#    #+#             */
/*   Updated: 2025-04-13 15:11:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_here_doc_fd(int **fd, int *io, int index, int argc)
{
	if (index == 3)
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

