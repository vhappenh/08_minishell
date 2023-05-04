/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:43 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/04 11:11:50 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

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
					ft_putendl_fd("exit", todo[i]->fd_out);
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