/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:03:29 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/17 14:13:16 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	open_files(t_pipex data, int io[2])
{
	if (ft_strncmp(data.argv[1], "here_doc", 8) == 0)
	{
		io[1] = open(data.argv[data.argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (io[1] == -1)
			error_handling(data, OPEN_FILE_ERROR);
		return ;
	}
	io[0] = open(data.argv[1], O_RDONLY);
	if (io[0] == -1)
		error_handling(data, OPEN_FILE_ERROR);
	io[1] = open (data.argv[data.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io[1] == -1)
		error_handling(data, OPEN_FILE_ERROR);
}

char	**find_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_executable_path(t_pipex data, char *command)
{
	char	*full_path;
	int		index;
	char	*cmd_path;

	if (!data.path)
		return (ft_strdup(command));
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	index = 0;
	while (data.path[index])
	{
		cmd_path = ft_strjoin(data.path[index], "/");
		full_path = ft_strjoin(cmd_path, command);
		free(cmd_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		index++;
	}
	return (ft_strdup(command));
}
