/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:43 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/11 10:58:17 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_get_exit_code(char *cmd, int fd, int *e)
{
	int	j;

	j = -1;
	while (cmd[++j])
	{
		if (!ft_isdigit(cmd[j]))
		{
			ft_putendl_fd("exit", fd);
			ft_putstr_fd("minishell: exit:", fd);
			ft_putstr_fd(cmd, fd);
			ft_putendl_fd(": numeric argument required", fd);
			break ;
		}
		else
			*e = (unsigned char)ft_atoi(cmd);
	}
}

int	ft_exit(t_cmdline **todo, t_envlst *env, int i)
{
	int	e;

	e = 2;
	if (todo[i]->cmd[1])
	{
		if (todo[i]->cmd[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments",
				todo[i]->fd_out);
			return (1);
		}
		else
			ft_get_exit_code(todo[i]->cmd[1], todo[i]->fd_out, &e);
	}
	else
		e = 0;
	ft_free_all(todo, env, NULL);
	clear_history();
	if (e)
		exit (e);
	exit (g_error);
	return (0);
}
