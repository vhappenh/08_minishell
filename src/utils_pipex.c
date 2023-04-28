/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:20:03 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/28 14:08:41 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static char	*ft_get_path(char *arg, char *path[])
{
	char	*fin;
	int		i;

	i = 0;
	while (path[i])
	{
		fin = ft_doublejoin(path[i], "/", arg);
		if (fin == NULL)
			return (NULL);
		if (access(fin, X_OK) == 0)
			break ;
		free(fin);
		fin = NULL;
		i++;
	}
	if (fin == NULL)
		return (arg);
	free(arg);
	return (fin);
}

int	ft_prep_cmd(t_cmdline *todo)
{
	char	**path;
	int		i;

	i = 0;
	while (todo->env[i] && ft_strncmp(todo->env[i], "PATH=", 5))
		i++;
	if (todo->env[i] != NULL)
	{
		path = ft_split(&todo->env[i][5], ':');
		todo->cmd[0] = ft_get_path(todo->cmd[0], path);
		if (todo->cmd[0] == NULL)
		{
			todo->cmd[0] = ft_strdup("");
			return (1);
		}
	}
	return (0);
}
