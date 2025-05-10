/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:56:38 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/18 20:47:14 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;

	data = malloc(sizeof(t_pipex));
	if (!data)
		error_handling(data, MALLOC_ERROR);
	ft_memset(data, 0, sizeof(t_pipex));
	if (argc < 5)
		error_handling(data, INVALID_INPUT);
	init_pipex(data, argc, argv, envp);
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		if (argc < 6)
			error_handling(data, INVALID_INPUT);
		data->doc_flag = 1;
		here_doc(data);
	}
	else
		pipex(data);
	close_fds(data);
	while (wait(NULL) != -1)
		;
	ft_free_matrix(&data->path);
	close_io(data->io);
	free(data);
	return (0);
}
