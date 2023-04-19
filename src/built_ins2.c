/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/19 10:45:30 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_env(t_envlst *env, int fd)
{
	while (env)
	{
		ft_putendl_fd(env->evar, fd);
		write(fd, "=", 1);	
		ft_putendl_fd(env->cont, fd);
		env = env->next;
	}
	return (0);
}

int	ft_exit(t_cmdline **todo, t_envlst *env)
{
	ft_free_all(todo, env, NULL);
	clear_history();
	exit (1);
	return (0);
}

int	ft_unset(t_cmdline *todo, t_envlst *env)
{
	t_envlst	*head;
	t_envlst	*temp;
	int			i;

	i = 0;
	while (todo->cmd[++i])
	{
		head = env;
		temp = head;
		while (head)
		{
			if (!ft_strncmp(todo->cmd[i], head->evar, ft_strlen(todo->cmd[i]) + 1))
				if (!ft_found_target(&temp, &head))
					break ;
			if (!(temp == head))
				temp = temp->next;
			head = head->next;
		}
	}	
	return (0);
}
