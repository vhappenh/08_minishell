/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/21 17:46:21 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_env(t_envlst *env, int fd, t_cmdline *todo)
{
	if (todo->cmd[1])
		ft_putendl_fd("minishell: too many arguments", todo->fd_out);
	else
	{
		while (env)
		{
			ft_putstr_fd(env->evar, fd);
			write(fd, "=", 1);
			ft_putendl_fd(env->cont, fd);
			env = env->next;
		}
	}
	return (0);
}

int	ft_exit(t_cmdline **todo, t_envlst *env, int i)
{
	int	e;
	int	j;

	e = 2;
	j = -1;
	if (todo[i]->cmd[1])
	{
		if (todo[i]->cmd[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments",
				todo[i]->fd_out);
			return (1);
		}
		else
		{
			while (todo[i]->cmd[1][++j])
			{
				if (!ft_isdigit(todo[i]->cmd[1][j]))
				{
					ft_putstr_fd("minishell: exit:", todo[i]->fd_out);
					ft_putstr_fd(todo[i]->cmd[1], todo[i]->fd_out);
					ft_putendl_fd(": numeric argument required",
						todo[i]->fd_out);
					break ;
				}
				else
					e = (char)ft_atoi(todo[i]->cmd[1]);
			}
		}
	}
	else
		e = 0;
	ft_free_all(todo, env, NULL);
	clear_history();
	if (e)
		exit (e);
	exit (errno);
	return (0);
}

int	ft_unset(t_cmdline *todo, t_envlst *env)
{
	t_envlst	*head;
	t_envlst	*temp;
	int			i;

	i = 0;
	while (todo->cmd[++i])
	{
		head = env;
		temp = head;
		while (head)
		{
			if (!ft_strncmp(todo->cmd[i], head->evar,
					ft_strlen(todo->cmd[i]) + 1))
				if (!ft_found_target(&temp, &head))
					break ;
			if (!(temp == head))
				temp = temp->next;
			head = head->next;
		}
	}	
	return (0);
}
