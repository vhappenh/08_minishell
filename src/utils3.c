/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/05 09:29:39 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	save_pwd(t_envlst *env, char *pwd)
{
	while (env)
	{
		if (!ft_strncmp(env->evar, "PWD", 4))
		{
			free (env->cont);
			env->cont = ft_strdup(pwd);
			if (env->cont == NULL)
				return (1);
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	save_old_pwd(t_envlst *env, char *pwd)
{
	while (env)
	{
		if (!ft_strncmp(env->evar, "OLDPWD", 7))
		{
			free (env->cont);
			env->cont = ft_strdup(pwd);
			if (env->cont == NULL)
				return (1);
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	cd_dot_dot(char *pwd, char **new_path)
{
	int	i;
	int	new_len;

	i = -1;
	while (pwd[++i])
		if (pwd[i] == '/')
			new_len = i;
	if (new_len == 0)
	{
		*new_path = ft_calloc(sizeof(char), 1 + 1);
		if (*new_path == NULL)
			return (1);
		*new_path = ft_memcpy(*new_path, "/", 1);
	}
	else
	{
		*new_path = ft_calloc(sizeof(char), new_len + 1);
		if (*new_path == NULL)
			return (2);
		*new_path = ft_memcpy(*new_path, pwd, new_len);
	}
	return (0);
}

int	ft_lvl_up(t_envlst **lst)
{
	char	*cont;
	int		lvl;

	lvl = ft_atoi((*lst)->cont);
	if (lvl == 9)
		return (1);
	lvl++;
	free ((*lst)->cont);
	cont = ft_itoa(lvl);
	if (cont == NULL)
		return (2);
	(*lst)->cont = cont;
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
	if (temp1 == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (2);
	}
	lst = ft_lstnew_minishell(temp1, temp2, 0);
	if (lst == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (3);
	}
	ft_lstadd_back_minishell(env, lst);
	return (0);
}
