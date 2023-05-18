/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:45 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/18 13:11:25 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_execute(t_cmdline *todo, int fd_in, int fd_out)
{
	ft_prep_exe(todo, fd_in, fd_out);
	if (todo->fd_in == -1 || todo->fd_out == -1)
		return (ft_free_close(todo, NULL, NULL));
	if (!ft_built_in_check(&todo, 0))
	{
		ft_built_in_select(&todo, 0, todo->enviroment);
		return (ft_free_close(todo, NULL, NULL));
	}
	if (lst_to_ptr(todo->enviroment, &todo->env) == -1)
		return (ft_free_close(todo, NULL, NULL));
	if (todo->cmd)
		if (ft_prep_cmd(todo))
			return (ft_free_close(todo, "minishell", NULL));
	if ((todo->cmd[0][0] == '/' || todo->cmd[0][0] == '.')
		&& access(todo->cmd[0], F_OK) == -1)
		return (ft_free_close(todo, "minishell", NULL));
	if (todo->fd_in != 0)
		if (dup2(todo->fd_in, 0) == -1)
			return (ft_free_close(todo, "minishell", NULL));
	if (todo->fd_out != 1)
		if (dup2(todo->fd_out, 1) == -1)
			return (ft_free_close(todo, "minishell", NULL));
	if (execve(todo->cmd[0], todo->cmd, todo->env) == -1)
		ft_free_close(todo, NULL, todo->cmd[0]);
}

static void	ft_child(t_cmdline **t, int i, int j)
{
	ft_switch_signals(CHILD);
	if (i == 0 && t[i + 1] == NULL)
	{
		ft_close_pipes((*t)->pipe_fds[i][0], (*t)->pipe_fds[i][1]);
		ft_execute(t[i], 0, 1);
	}
	else if (i == 0)
	{
		close((*t)->pipe_fds[i][0]);
		ft_execute(t[i], 0, (*t)->pipe_fds[i][1]);
	}
	else if (t[i + 1] == NULL)
	{
		ft_close_pipes((*t)->pipe_fds[i][1], (*t)->pipe_fds[i][0]);
		ft_execute(t[i], (*t)->pipe_fds[i - 1][0], 1);
	}
	else
	{
		close((*t)->pipe_fds[i][0]);
		ft_execute(t[i], (*t)->pipe_fds[i - 1][0], (*t)->pipe_fds[i][1]);
	}
	ft_free_exe((*t)->pids, (*t)->pipe_fds, j);
	ft_free_all(t, t[0]->enviroment, NULL);
	exit(g_error);
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

static int	ft_wait_for_children(t_cmdline **todo, int i)
{
	int	err;
	int	j;

	err = 0;
	j = 0;
	while (j < i)
	{
		if (waitpid((*todo)->pids[j++], &err, 0) == -1)
		{
			ft_free_exe((*todo)->pids, (*todo)->pipe_fds, i);
			return (-1);
		}
	}
	ft_switch_signals(INTERACTIV);
	if (WEXITSTATUS(err))
		g_error = WEXITSTATUS(err);
	else if (WTERMSIG(err))
		g_error = WTERMSIG(err) + 128;
	else
		g_error = 0;
	if (i)
		ft_free_exe((*todo)->pids, (*todo)->pipe_fds, i);
	return (0);
}

int	ft_execution(t_cmdline **todo)
{
	int	i;

	i = 0;
	if ((*todo) == NULL || todo[0]->cmd[0] == NULL)
		return (0);
	i = ft_init_exe(todo, i);
	if (i == -1)
		return (1);
	if (i == 1 && todo[1] == NULL && !ft_built_in_check(todo, 0))
	{
		ft_free_exe((*todo)->pids, (*todo)->pipe_fds, i);
		ft_prep_exe(todo[0], 0, 1);
		ft_built_in_select(todo, 0, todo[0]->enviroment);
		ft_free_all(NULL, NULL, todo[0]->env);
		i = 0;
		if (g_error == -1)
			return (-1);
	}
	else
		if (ft_fork_it(todo, i))
			return (1);
	if (i > 0 && ft_wait_for_children(todo, i) == -1)
		return (-1);
	return (0);
}
