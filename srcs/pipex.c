/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:56:38 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/17 14:07:33 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	ft_memset(&data, 0, sizeof(t_pipex));
	data.io[0] = -1;
	data.io[1] = -1;
	if (argc < 5)
		error_handling(data, INVALID_INPUT);
	init_pipex(&data, argc, argv, envp);
	if (strcmp("here_doc", argv[1]) == 0)
	{
		if (argc < 6)
			error_handling(data, INVALID_INPUT);
		data.doc_flag = 1;
		here_doc(data);
	}
	else
		pipex(data);
	close_fds(data);
	while (wait(NULL) != -1)
		;
	ft_free_matrix(data.path);
	close_io(data.io);
	return (0);
}
