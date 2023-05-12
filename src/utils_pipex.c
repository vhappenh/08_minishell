/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:20:03 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/12 09:37:31 by rrupp            ###   ########.fr       */
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

int	ft_init_exe(t_cmdline **todo, int i)
{
	int	j;

	j = 0;
	while (todo[i])
		i++;
	(*todo)->pids = malloc(i * sizeof(pid_t));
	if ((*todo)->pids == NULL)
		return (-1);
	(*todo)->pipe_fds = ft_calloc(i + 1, sizeof(int *));
	if ((*todo)->pipe_fds == NULL)
	{
		free ((*todo)->pids);
		return (-1);
	}
	while (j <= i)
	{
		((*todo)->pipe_fds)[j] = ft_calloc(2, sizeof(int));
		if (((*todo)->pipe_fds)[j] == NULL)
		{
			ft_free_exe((*todo)->pids, (*todo)->pipe_fds, j);
			return (-1);
		}
		j++;
	}
	return (i);
}

void	ft_prep_exe(t_cmdline *todo, int fd_in, int fd_out)
{
	if (todo->in_file)
		todo->fd_in = open(todo->in_file, O_RDONLY);
	else
		todo->fd_in = fd_in;
	if (todo->out_file)
		todo->fd_out = open(todo->out_file, O_WRONLY | O_APPEND);
	else
		todo->fd_out = fd_out;
}
