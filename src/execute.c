/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:30:41 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/16 14:37:21 by vhappenh         ###   ########.fr       */
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
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			*paths = ft_strdup(envp[i]);
			if (paths == NULL)
				return (1);
		}
	}
	i = -1;
	return (0);
}

static int	split_paths(char **paths, char **path, t_cmdline **todo)
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

int	execute(t_cmdline **todo, char **envp)
{
	static char	*paths;
	static char	*path;

	if (find_paths(envp, &paths))
		return (1);
	if (split_paths(&paths, &path, todo))
		return (2);
	free (path);
	return (0);
}
/*	have to fork before and then call this in the child
	if (execve(path, todo[0]->cmd, envp) < 0)
	{
		free (path);
		return (3);
	} */
