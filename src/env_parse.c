/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/06 16:11:28 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_get_inputs(char *envp, t_envlst **lst)
{
	char		*evar;
	char		*cont;

	evar = ft_strncopy(envp, ft_search_char(envp, '='));
	cont = ft_strdup(envp + ft_search_char(envp, '=') + 1);
	*lst = ft_lstnew_minishell(evar, cont, 0);
	if (lst == NULL)
		return (3);
	return (0);
}

int	ft_parse_env(char **envp, t_envlst **env)
{
	int			i;
	bool		shlvl;
	t_envlst	*lst;

	i = -1;
	shlvl = true;
	while (envp[++i])
	{
		if (ft_get_inputs(envp[i], &lst))
			return (1);
		if (!ft_strncmp(lst->evar, "SHLVL", 6))
		{
			if (ft_lvl_up(&lst))
				if (!ft_free_lvl_fail(&lst, env))
					return (3);
			shlvl = false;
		}
		ft_lstadd_back_minishell(env, lst);
	}
	if (shlvl)
		if (ft_add_shlvl(env))
			return (3);
	return (0);
}
