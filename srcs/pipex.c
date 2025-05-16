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

	if (argc < 5 || (ft_strcmp("here_doc", argv[1]) == 0 && argc < 6))
		return (ft_putstr_fd("❌ \033[31mError: Invalid input\e[0m\n", 2), 0);
	data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		return (0);
	init_pipex(data, argc, argv, envp);
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		data->doc_flag = 1;
		here_doc(data);
	}
	else
		pipex(data);
	close_fds(data);
	while (wait(NULL) != -1)
		;
	ft_free_matrix(data->path);
	close_io(data->io);
	free(data);
	return (0);
}
