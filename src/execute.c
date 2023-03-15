/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:30:41 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/15 18:05:03 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	execute(t_cmdline **todo, char **envp)
{
	int		i;
	int		j;
	char	*paths;
	char	*temp1;
	char	*temp2;
	char	**split_paths;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			paths = ft_strdup(envp[i]);
			if (paths == NULL)
				return (1);
		}
	}
	i = -1;
	while (++i < 5)
		paths++;
	split_paths = ft_split(paths, ':');
	if (split_paths == NULL)
	{
		free (paths);
		return (2);
	}
	i = -1;
	while (split_paths[++i])
	{
		temp1 = ft_strjoin(split_paths[i], "/");
		temp2 = ft_strjoin(temp1, todo[0]->cmd[0]);
		free (temp1);
		if (access(temp2, X_OK) == 0)
			break ;
	}
	if (execve(temp2, todo[0]->cmd, envp) < 0)
		return (3);
	return (0);
}
