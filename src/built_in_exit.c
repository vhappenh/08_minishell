/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:43 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/28 15:16:07 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_print_exit_error(char *cmd, int fd)
{
	ft_putstr_fd("minishell: exit:", fd);
	ft_putstr_fd(cmd, fd);
	ft_putendl_fd(": numeric argument required", fd);
}

static void	ft_get_exit_code(char *cmd, int fd, int *e)
{
	int		j;

	j = -1;
	if (cmd[0] == '+' || cmd [0] == '-')
		j++;
	while (cmd[++j])
	{
		if (!ft_isdigit(cmd[j]))
		{
			ft_print_exit_error(cmd, fd);
			return ;
		}
	}
	*e = (unsigned char) ft_atoi_long(cmd, &j);
	if (j == -1)
	{
		ft_print_exit_error(cmd, fd);
		*e = 2;
	}
}

static int	ft_exit_destiny(t_cmdline **todo, t_envlst *env)
{
	if (!todo[1])
	{
		write (1, "exit\n", 5);
		ft_free_all(todo, env, NULL);
		clear_history();
	}
	else
		return (0);
	return (1);
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
	if (!ft_exit_destiny(todo, env))
		return (e);
	if (e)
		exit (e);
	exit (g_error);
	return (0);
}
