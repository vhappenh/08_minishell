/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/28 11:08:00 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_create_pwd(char **envp, t_envlst **env)
{
	t_envlst	*temp;
	bool		findy;
	char		*pwd;
	int			i;

	i = -1;
	findy = true;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PWD=", 4))
			findy = false;
	if (findy)
	{
		if (ft_get_pwd(&pwd))
			return (-1);
		temp = ft_lstnew_minishell(ft_strdup("PWD"), ft_strdup(pwd), false);
		free (pwd);
		if (temp == NULL)
			return (-1);
		ft_lstadd_back_minishell(env, temp);
	}
	return (0);
}

static int	ft_create_hidyhead(char **envp, t_envlst **env)
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
	free (pwd);
	if (temp == NULL)
		return (-1);
	temp->hidy = true;
	ft_lstadd_back_minishell(env, temp);
	return (ft_create_pwd(envp, env));
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
	if (ft_create_hidyhead(envp, env))
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
