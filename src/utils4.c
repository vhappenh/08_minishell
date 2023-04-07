/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/06 13:54:04 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_found_target(t_envlst **temp, t_envlst **head)
{
	free ((*head)->line);
	(*temp)->next = (*head)->next;
	free (*head);
	return (0);
}

int	ft_free_lvl_fail(t_envlst **lst, t_envlst **env)
{
	free ((*lst)->line);
	free (*lst);
	ft_free_all(NULL, *env, NULL);
	return (0);
}
