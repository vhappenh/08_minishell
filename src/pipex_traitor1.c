/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_traitor1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:45 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/29 12:43:23 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_execute(t_cmdline *todo, int fd_in, int fd_out)
{
	if (todo->in_file)
		todo->fd_in = open(todo->in_file, O_RDONLY);
	else
		todo->fd_in = fd_in;
	if (todo->out_file)
		todo->fd_out = open(todo->out_file, O_WRONLY);
	else
		todo->fd_out = fd_out;
	if (lst_to_ptr(todo->enviroment, &todo->env))
		return ;
	if (todo->cmd)
		if (ft_prep_cmd(todo))
			return ;
	if (dup2(todo->fd_in, 0) == -1 || dup2(todo->fd_out, 1) == -1)
		return ;
	if (execve(todo->cmd[0], todo->cmd, todo->env) == -1)
	{
		if (todo->fd_in != 0)
			close(todo->fd_in);
		if (todo->fd_out != 1)
			close(todo->fd_out);
		ft_free_all(NULL, todo->enviroment, todo->env);
	}
}

static void	ft_child(t_cmdline **t, int i, int j)
{
	if (i == 0 && t[i + 1] == NULL)
	{
		close ((*t)->pipe_fds[i][0]);
		close ((*t)->pipe_fds[i][1]);
		ft_execute(t[i], 0, 1);
	}
	else if (i == 0)
	{
		close((*t)->pipe_fds[i][0]);
		ft_execute(t[i], 0, (*t)->pipe_fds[i][1]);
	}
	else if (t[i + 1] == NULL)
	{
		close((*t)->pipe_fds[i][1]);
		ft_execute(t[i], (*t)->pipe_fds[i - 1][0], 1);
	}
	else
		ft_execute(t[i], (*t)->pipe_fds[i - 1][0], (*t)->pipe_fds[i][1]);
	ft_free_exe((*t)->pids, (*t)->pipe_fds, j);
	exit(0);
}

static int	ft_fork_it(t_cmdline **todo, int j)
{
	int	i;

	i = 0;
	while (todo[i])
	{
		if (pipe((*todo)->pipe_fds[i]))
			return (1);
		(*todo)->pids[i] = fork();
		if ((*todo)->pids[i] == -1)
			return (1);
		if ((*todo)->pids[i] == 0)
			ft_child(todo, i, j);
		else
		{
			close((*todo)->pipe_fds[i][1]);
			if (i != 0)
				close((*todo)->pipe_fds[i - 1][0]);
		}
		ft_free_all(NULL, NULL, todo[i]->env);
		i++;
	}
	if ((*todo)->pipe_fds[i][0])
		close((*todo)->pipe_fds[i][0]);
	return (0);
}

int	ft_execution(t_cmdline **todo)
{
	int		i;
	int		j;

	i = 0;
	i = ft_init_exe(todo, i);
	if (i == -1)
		return (1);
	if (i == 1 && todo[1] == NULL
		&& !ft_built_in_check(todo, 0, todo[0]->enviroment, 1))
		;
	else
		if (ft_fork_it(todo, i))
			return (1);
	j = 0;
	while (j < i)
		waitpid((*todo)->pids[j++], &errno, 0);
	errno = WEXITSTATUS(errno);
	ft_free_exe((*todo)->pids, (*todo)->pipe_fds, i);
	return (0);
}
