/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:08:05 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/27 15:25:22 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_found_target(t_envlst **temp, t_envlst **head, t_envlst **env)
{
	free ((*head)->evar);
	free ((*head)->cont);
	if ((*head) == (*env))
		(*env) = (*env)->next;
	else
		(*temp)->next = (*head)->next;
	free (*head);
	return (0);
}

int	ft_unset(t_cmdline *todo, t_envlst **env)
{
	t_envlst	*head;
	t_envlst	*temp;
	int			i;

	i = 0;
	while (todo->cmd[++i])
	{
		head = *env;
		temp = head;
		while (head)
		{
			if (!ft_strncmp(todo->cmd[i], head->evar,
					ft_strlen(todo->cmd[i]) + 1))
			{
				ft_found_target(&temp, &head, env);
				break ;
			}
			if (!(temp == head))
				temp = temp->next;
			head = head->next;
		}
	}	
	return (0);
}
