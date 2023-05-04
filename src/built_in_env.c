/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:10:10 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/04 11:10:18 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_env(t_envlst *env, t_cmdline *todo)
{
	if (todo->cmd[1])
		ft_putendl_fd("minishell: too many arguments", todo->fd_out);
	else
	{
		while (env)
		{
			if (!env->indic)
			{
				ft_putstr_fd(env->evar, todo->fd_out);
				write(todo->fd_out, "=", 1);
				ft_putendl_fd(env->cont, todo->fd_out);
			}
			env = env->next;
		}
	}
	return (0);
}