/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/27 17:20:28 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_create_hidyplus(t_envlst **lst)
{
	t_envlst	*temp1;
	t_envlst	*temp2;

	temp1 = ft_lstnew_minishell(ft_strdup("~+"), ft_strdup("$PWD"), false);
	if (temp1 == NULL)
		return (-1);
	temp1->hidy = true;
	ft_lstadd_back_minishell(lst, temp1);
	temp2 = ft_lstnew_minishell(ft_strdup("~-"), ft_strdup("$OLDPWD"), false);
	if (temp2 == NULL)
		return (-1);
	temp2->hidy = true;
	ft_lstadd_back_minishell(lst, temp2);
	return (0);
}

static int	ft_create_hidyhead(t_envlst **lst)
{
	t_envlst	*temp;
	char		*pwd;
	int			i;
	int			j;

	if (ft_get_pwd(&pwd))
		return (-1);
	i = -1;
	j = 0;
	while (pwd[++i])
	{
		if (pwd[i] == '/')
			j++;
		if (j == 4)
			break ;
	}
	temp = ft_lstnew_minishell(ft_strdup("~"),
			ft_strncopy(pwd, i), false);
	if (temp == NULL)
		return (-1);
	temp->hidy = true;
	ft_lstadd_back_minishell(lst, temp);
	return (ft_create_hidyplus(lst));
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
	}
	if (shlvl)
		if (ft_add_shlvl(env))
			return (4);
	return (0);
}
