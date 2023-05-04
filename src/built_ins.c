/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/04 11:16:43 by vhappenh         ###   ########.fr       */
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

int	ft_built_in_select(t_cmdline **todo, int i, t_envlst *env)
{
	if (!ft_strncmp((todo[i])->cmd[0], "echo", 5))
		return (ft_echo(todo[i]));
	else if (!ft_strncmp(todo[i]->cmd[0], "cd", 3))
		return (ft_cd(todo[i], env));
	else if (!ft_strncmp(todo[i]->cmd[0], "pwd", 4))
		return (ft_pwd(todo[i]->fd_out));
	else if (!ft_strncmp(todo[i]->cmd[0], "export", 7))
		return (ft_export(todo[i], env));
	else if (!ft_strncmp(todo[i]->cmd[0], "unset", 6))
		return (ft_unset(todo[i], env));
	else if (!ft_strncmp(todo[i]->cmd[0], "env", 4))
		return (ft_env(env, todo[i]));
	else if (!ft_strncmp(todo[i]->cmd[0], "exit", 5))
		return (ft_exit(todo, env, i));
	else
		return (1);
}
