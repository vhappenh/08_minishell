/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_traitor1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:45 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/02 13:09:37 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_close_free(t_cmdline *todo)
{
	if (todo->fd_in != 0)
		close(todo->fd_in);
	if (todo->fd_out != 1)
		close(todo->fd_out);
	ft_free_all(NULL, todo->enviroment, todo->env);
}

void	ft_execute(t_cmdline *todo, int fd_in, int fd_out)
{
	ft_prep_inoutenv(todo, fd_in, fd_out);
	if (!ft_built_in_check(&todo, todo->nbr, todo->enviroment))
		return (ft_close_free(todo));
	if (todo->cmd)
		if (ft_prep_cmd(todo))
			return ;
	if (dup2(todo->fd_in, 0) == -1 || dup2(todo->fd_out, 1) == -1)
		return ;
	if (execve(todo->cmd[0], todo->cmd, todo->env) == -1)
		ft_close_free(todo);
}

static void	ft_child(t_cmdline **t, int i, int j)
{
	ft_switch_signals(CHILD);
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
	ft_switch_signals(EXECUTING);
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
	if (todo[0]->cmd[0] == NULL)
		return (0);
	i = ft_init_exe(todo, i);
	if (i == -1)
		return (1);
	if (i == 1 && todo[1] == NULL
		&& !ft_built_in_check(todo, 0, todo[0]->enviroment))
		;
	else
		if (ft_fork_it(todo, i))
			return (1);
	j = 0;
	while (j < i)
		waitpid((*todo)->pids[j++], &errno, 0);
	ft_switch_signals(INTERACTIV);
	errno = WEXITSTATUS(errno);
	ft_free_exe((*todo)->pids, (*todo)->pipe_fds, i);
	return (0);
}
