/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/05 13:58:33 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_env(t_envlst *env, int fd)
{
	int	i;

	i = -1;
	while (env)
	{
		ft_putendl_fd(env->line, fd);
		env = env->next;
	}
	return (0);
}

int	ft_exit(t_cmdline **todo, t_envlst *env)
{
	ft_free_all(todo, env, NULL);
	exit (1);
	return (0);
}

int	ft_unset(t_cmdline *todo, t_envlst *env)
{
	return (0);
}
