/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:04:03 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/09 15:09:48 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_lvl_up(t_envlst **lst)
{
	char	*cont;
	int		lvl;

	lvl = ft_atoi((*lst)->cont);
	if (lvl >= 9)
		return (1);
	lvl++;
	free ((*lst)->cont);
	cont = ft_itoa(lvl);
	if (cont == NULL)
		return (2);
	(*lst)->cont = cont;
	return (0);
}

int	ft_free_lvl_fail(t_envlst **lst, t_envlst **env)
{
	free ((*lst)->evar);
	free ((*lst)->cont);
	free (*lst);
	ft_free_all(NULL, *env, NULL);
	return (0);
}

int	ft_add_shlvl(t_envlst **env)
{
	char		*temp1;
	char		*temp2;
	t_envlst	*lst;

	temp1 = ft_strdup("SHLVL");
	if (temp1 == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (1);
	}
	temp2 = ft_strdup("1");
	if (temp2 == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (2);
	}
	lst = ft_lstnew_minishell(temp1, temp2, false);
	if (lst == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (3);
	}
	ft_lstadd_back_minishell(env, lst);
	return (0);
}
