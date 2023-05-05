/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:08:05 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/05 09:35:16 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

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
			if (!ft_strncmp(todo->cmd[i], head->evar,
					ft_strlen(todo->cmd[i]) + 1))
				if (!ft_found_target(&temp, &head))
					break ;
			if (!(temp == head))
				temp = temp->next;
			head = head->next;
		}
	}	
	return (0);
}
