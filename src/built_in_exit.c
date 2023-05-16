/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:43 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/16 10:19:56 by rrupp            ###   ########.fr       */
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
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		else
			ft_get_exit_code(todo[i]->cmd[1], 2, &e);
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
