/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/06 13:46:06 by vhappenh         ###   ########.fr       */
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
	clear_history();
	exit (1);
	return (0);
}

int	ft_unset(t_cmdline *todo, t_envlst *env)
{
	t_envlst	*head;
	t_envlst	*temp;
	char		*joined;
	int			i;

	i = 0;
	while (todo->cmd[++i])
	{
		joined = ft_strjoin(todo->cmd[i], "=");
		if (joined == NULL)
			return (1);
		head = env;
		temp = head;
		while (head)
		{
			if (!ft_strncmp(joined, head->line, ft_strlen(joined)))
				if (!ft_found_target(&temp, &head))
					break ;
			if (!(temp == head))
				temp = temp->next;
			head = head->next;
		}
		free (joined);
	}	
	return (0);
}
