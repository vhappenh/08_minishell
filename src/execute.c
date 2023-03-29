/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:30:41 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/29 11:56:31 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	find_paths(char **envp, char **paths)
{
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			*paths = ft_strdup(envp[i]);
			if (paths == NULL)
				return (1);
		}
	}
	i = -1;
	return (0);
}

static int	split_paths(char **paths, char **path, t_cmdline *todo)
{
	int		i;
	char	**split_paths;

	split_paths = ft_split(&(*paths)[5], ':');
	if (split_paths == NULL)
		return (1);
	free (*paths);
	i = -1;
	while (split_paths[++i])
	{
		if (!ft_doublejoin(split_paths[i], path, todo))
			break ;
	}
	i = -1;
	while (split_paths[++i])
		free (split_paths[i]);
	free (split_paths);
	return (0);
}

static int	ft_fork(t_cmdline *todo, char **envp, char *path)
{
	int			id;

	id = fork();
	if (id != 0)
		wait(NULL);
	else
	{
		if (execve(path, todo->cmd, envp) < 0)
			return (1);
	}
	free (path);
	return (0);
}

int	execute(t_cmdline **todo, char **envp)
{
	static char	*paths;
	static char	*path;
	int			i;
	int			fd;

	fd = 1;
	i = -1;
	while (todo[++i])
	{
		if (ft_built_in_check(todo[i], fd))
			return (4);
		if (find_paths(envp, &paths))
			return (1);
		if (split_paths(&paths, &path, todo[i]))
			return (2);
		if (ft_fork(todo[i], envp, path))
			return (3);
	}
	return (0);
}
