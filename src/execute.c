/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:30:41 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/31 14:40:51 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	find_paths(char **env, char **paths)
{
	int		i;

	i = get_env_path(env, "PATH");
	*paths = ft_strdup(env[i]);
	if (paths == NULL)
		return (1);
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
		if (!ft_djoin_spec(split_paths[i], path, todo))
			break ;
	}
	i = -1;
	while (split_paths[++i])
		free (split_paths[i]);
	free (split_paths);
	return (0);
}

static int	ft_fork(t_cmdline *todo, char **env, char *path)
{
	int			id;

	id = fork();
	if (id != 0)
		wait(NULL);
	else
	{
		if (execve(path, todo->cmd, env) < 0)
			return (1);
	}
	free (path);
	return (0);
}

int	execute(t_cmdline **todo, char **env)
{
	static char	*paths;
	static char	*path;
	int			i;
	int			fd;

	fd = 1;
	i = -1;
	while (todo[++i])
	{
		if (!ft_built_in_check(todo[i], env, fd))
			;
		else
		{
			if (find_paths(env, &paths))
				return (2);
			if (split_paths(&paths, &path, todo[i]))
				return (3);
			if (ft_fork(todo[i], env, path))
				return (4);
		}
	}
	return (0);
}
