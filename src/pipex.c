/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:45 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/11 11:00:40 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_close_free(t_cmdline *todo, char *err1, char *err2)
{
	if (todo->fd_in != 0)
		close(todo->fd_in);
	if (todo->fd_out != 1)
		close(todo->fd_out);
	ft_free_all(NULL, todo->enviroment, todo->env);
	if (err1)
	{
		perror(err1);
	}
	if (err2)
	{
		ft_putstr_fd(err2, 2);
		ft_putendl_fd(": command not found", 2);
		errno = 127;
	}
}

void	ft_execute(t_cmdline *todo, int fd_in, int fd_out)
{
	ft_prep_inoutenv(todo, fd_in, fd_out);
	if (!ft_built_in_check(&todo, 0))
	{
		ft_built_in_select(&todo, 0, todo->enviroment);
		return (ft_close_free(todo, NULL, NULL));
	}
	if (todo->cmd)
		if (ft_prep_cmd(todo))
			return ;
	if (todo->fd_in != 0)
		if (dup2(todo->fd_in, 0) == -1)
			return (ft_close_free(todo, "minishell: ", NULL));
	if (todo->fd_out != 1)
		if (dup2(todo->fd_out, 1) == -1)
			return (ft_close_free(todo, "minishell: ", NULL));
	if (execve(todo->cmd[0], todo->cmd, todo->env) == -1)
		ft_close_free(todo, NULL, todo->cmd[0]);
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

int	ft_execution(t_cmdline **todo)
{
	int	i;
	int	j;
	int	err;

	i = 0;
	err = 0;
	if (todo[0]->cmd[0] == NULL)
		return (0);
	i = ft_init_exe(todo, i);
	if (i == -1)
		return (1);
	if (i == 1 && todo[1] == NULL && !ft_built_in_check(todo, 0))
	{
		ft_prep_inoutenv(todo[0], 0, 1);
		i = 0;
		ft_built_in_select(todo, 0, todo[0]->enviroment);
		if (g_error == -1)
			return (-1);
	}
	else
		if (ft_fork_it(todo, i))
			return (1);
	j = 0;
	while (j < i)
		waitpid((*todo)->pids[j++], &err, 0);
	ft_switch_signals(INTERACTIV);
	if (WEXITSTATUS(err))
		g_error = WEXITSTATUS(err);
	else if (WTERMSIG(err))
		g_error = WTERMSIG(err);
	ft_free_exe((*todo)->pids, (*todo)->pipe_fds, i);
	return (0);
}
