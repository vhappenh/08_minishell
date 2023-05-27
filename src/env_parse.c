/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/27 15:17:22 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_create_hidyhead(t_envlst **lst)
{
	t_envlst	*temp;

	temp = ft_lstnew_minishell(ft_strdup("whatdoesitdo"),
			ft_strdup("itshinesblue"), false);
	if (temp == NULL)
		return (-1);
	temp->hidy = true;
	ft_lstadd_back_minishell(lst, temp);
	return (0);
}

static int	ft_get_inputs(char *envp, t_envlst **lst)
{
	char		*evar;
	char		*cont;

	evar = ft_strncopy(envp, ft_search_char(envp, '='));
	cont = ft_strdup(envp + ft_search_char(envp, '=') + 1);
	*lst = ft_lstnew_minishell(evar, cont, false);
	if (lst == NULL)
		return (3);
	return (0);
}

static int	ft_create_tilde(char *env, t_envlst **lst)
{
	t_envlst	*temp;

	temp = ft_lstnew_minishell(ft_strdup("~"),
			ft_strdup(env + ft_search_char(env, '=') + 1), false);
	if (temp == NULL)
		return (-1);
	temp->hidy = true;
	ft_lstadd_back_minishell(lst, temp);
	return (0);
}

int	ft_parse_env(char **envp, t_envlst **env, int i)
{
	bool		shlvl;
	t_envlst	*lst;

	shlvl = true;
	if (ft_create_hidyhead(env))
		return (1);
	while (envp[++i])
	{
		if (ft_get_inputs(envp[i], &lst))
			return (2);
		if (!ft_strncmp(lst->evar, "SHLVL", 6))
		{
			if (ft_lvl_up(&lst))
				if (!ft_free_lvl_fail(&lst, env))
					return (3);
			shlvl = false;
		}
		ft_lstadd_back_minishell(env, lst);
		if (!ft_strncmp(lst->evar, "HOME", 5))
			ft_create_tilde(envp[i], &lst);
	}
	if (shlvl)
		if (ft_add_shlvl(env))
			return (4);
	return (0);
}
