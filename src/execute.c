/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:30:41 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/17 14:19:49 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	find_paths(t_envlst *env, char **paths)
{
	char	*path;

	path = get_env_path(env, "PATH=");
	*paths = ft_strdup(path);
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

static int	ft_fork(t_cmdline *todo, t_envlst *env, char *path)
{
	int		id;
	char	**env_ptr;

	id = fork();
	if (id != 0)
		wait(NULL);
	else
	{
		if (lst_to_ptr(env, &env_ptr))
			return (1);
		if (path == NULL)
		{
			path = ft_strdup(todo->cmd[0]);
			if (path == NULL)
				return (2);
		}
		if (execve(path, todo->cmd, env_ptr) < 0)
			return (3);
		ft_free_all(NULL, NULL, env_ptr);
	}
	free (path);
	return (0);
}

int	execute(t_cmdline **todo, t_envlst *env)
{
	static char	*paths;
	static char	*path;
	int			i;
	int			fd;

	i = -1;
	while (todo[++i])
	{
		if (!todo[i]->cmd[0])
			break ;
		if (!todo[i]->out_file)
			fd = 1;
		else
		{
			fd = open(todo[i]->out_file, O_WRONLY);
			if (fd == -1)
				return (1);
		}
		if (!ft_built_in_check(todo, i, env, fd))
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
		if (fd != 1)
			if (close(fd) == -1)
				return (5);
	}
	return (0);
}
