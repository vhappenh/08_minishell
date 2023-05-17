/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/17 15:39:38 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_built_in_check(t_cmdline **todo, int i)
{
	if (!ft_strncmp((todo[i])->cmd[0], "echo", 5))
		return (0);
	else if (!ft_strncmp(todo[i]->cmd[0], "cd", 3))
		return (0);
	else if (!ft_strncmp(todo[i]->cmd[0], "pwd", 4))
		return (0);
	else if (!ft_strncmp(todo[i]->cmd[0], "export", 7))
		return (0);
	else if (!ft_strncmp(todo[i]->cmd[0], "unset", 6))
		return (0);
	else if (!ft_strncmp(todo[i]->cmd[0], "env", 4))
		return (0);
	else if (!ft_strncmp(todo[i]->cmd[0], "exit", 5))
		return (0);
	else
		return (1);
}

void	ft_built_in_select(t_cmdline **todo, int i, t_envlst *env)
{
	if (!ft_strncmp((todo[i])->cmd[0], "echo", 5))
		g_error = ft_echo(todo[i]);
	else if (!ft_strncmp(todo[i]->cmd[0], "cd", 3))
		g_error = ft_cd(todo[i], env);
	else if (!ft_strncmp(todo[i]->cmd[0], "pwd", 4))
		g_error = ft_pwd(todo[i]->fd_out);
	else if (!ft_strncmp(todo[i]->cmd[0], "export", 7))
		g_error = ft_export(todo[i], env);
	else if (!ft_strncmp(todo[i]->cmd[0], "unset", 6))
		g_error = ft_unset(todo[i], &(*todo)->enviroment);
	else if (!ft_strncmp(todo[i]->cmd[0], "env", 4))
		g_error = ft_env(env, todo[i]);
	else if (!ft_strncmp(todo[i]->cmd[0], "exit", 5))
		g_error = ft_exit(todo, env, i);
	else
		g_error = 0;
}
