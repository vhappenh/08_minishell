/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_traitor1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:45 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/28 17:39:53 by rrupp            ###   ########.fr       */
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
		return;
	if (execve(todo->cmd[0], todo->cmd, todo->env) == -1)
	{
		if (todo->fd_in != 0)
			close(todo->fd_in);
		if (todo->fd_out != 1)
			close(todo->fd_out);
		ft_free_all(NULL, todo->enviroment, todo->env);
	}
}

static void	ft_free_exe(pid_t *pids, int **pipe_fds, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(pipe_fds[j++]);
	}
	free(pipe_fds);
	free(pids);
}

int	ft_execution(t_cmdline **todo)
{
	int		i;
	int		j;
	pid_t	*pids;
	int **pipe_fds;

	i = 0;
	j = 0;
	while (todo[i])
		i++;
	pids = malloc(i * sizeof(int));
	if (pids == NULL)
		return (1);
	pipe_fds = ft_calloc(i + 1, sizeof(int*));
	if (pipe_fds == NULL)
		return (1);
	while (j <= i)
	{
		pipe_fds[j] = ft_calloc(2, sizeof(int));
		if (pipe_fds[j] == NULL)
			return (1);
		j++;
	}
	if (i == 1 && todo[1] == NULL && !ft_built_in_check(todo, 0, todo[0]->enviroment, 1))
		;
	else
	{
		i = 0;
		while (todo[i])
		{
			if (pipe(pipe_fds[i]))
				return (1);
			pids[i] = fork();
			if (pids[i] == -1)
				return (1);
			if (pids[i] == 0)
			{
				if (i == 0 && todo[i + 1] == NULL)
				{
					close (pipe_fds[i][0]);
					close (pipe_fds[i][1]);
					ft_execute(todo[i], 0, 1);
					ft_free_exe(pids, pipe_fds, j);
					exit(0);
				}
				else if (i == 0)
				{
					close(pipe_fds[i][0]);
					ft_execute(todo[i], 0, pipe_fds[i][1]);
					ft_free_exe(pids, pipe_fds, j);
					exit(0);
				}
				else if (todo[i + 1] == NULL)
				{
					close(pipe_fds[i][1]);
					ft_execute(todo[i], pipe_fds[i - 1][0], 1);
					ft_free_exe(pids, pipe_fds, j);
					exit(0);
				}
				else
				{
					ft_execute(todo[i], pipe_fds[i - 1][0], pipe_fds[i][1]);
					ft_free_exe(pids, pipe_fds, j);
					exit(0);
				}
			}
			else
			{
				close(pipe_fds[i][1]);
				if (i != 0)
					close(pipe_fds[i - 1][0]);
			}
			ft_free_all(NULL, NULL, todo[i]->env);
			i++;
		}
		if (pipe_fds[i][0])
			close(pipe_fds[i][0]);
		j = 0;
		while (j < i)
			waitpid(pids[j++], &errno, 0);
		errno = WEXITSTATUS(errno);
	}
	ft_free_exe(pids, pipe_fds, i);
	return (0);
}
