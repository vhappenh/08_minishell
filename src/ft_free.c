/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:17 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/03 11:56:11 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_free_cmd(t_cmdline **todo)
{
	int	i;
	int	j;

	i = 0;
	if (todo)
	{
		while (todo[i])
		{
			if (todo[i]->in_file)
				free(todo[i]->in_file);
			if (todo[i]->out_file)
				free(todo[i]->out_file);
			if (todo[i]->cmd)
			{
				j = 0;
				while (todo[i]->cmd[j])
					free(todo[i]->cmd[j++]);
				free(todo[i]->cmd);
			}
			free(todo[i++]);
		}
		free(todo);
	}
}

void	ft_free_env(t_envlst *env)
{
	t_envlst	*temp;

	if (env)
	{
		while (env)
		{
			temp = env;
			env = env->next;
			free (temp);
		}
		free (env);
	}
}

void	ft_free_all(t_cmdline **todo, t_envlst *env)
{
	ft_free_cmd(todo);
	ft_free_env(env);
}
