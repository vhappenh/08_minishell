/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/03 12:05:30 by vhappenh         ###   ########.fr       */
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
	ft_free_all(todo, env);
	exit (1);
	return (0);
}
