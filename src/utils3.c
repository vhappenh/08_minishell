/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/06 13:29:19 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	save_pwd(t_envlst *env, char *pwd)
{
	while (env)
	{
		if (!ft_strncmp(env->line, "PWD=", 4))
		{
			free (env->line);
			env->line = ft_strjoin("PWD=", pwd);
			if (env->line == NULL)
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
		if (!ft_strncmp(env->line, "OLDPWD=", 7))
		{
			free (env->line);
			env->line = ft_strjoin("OLDPWD=", pwd);
			if (env->line == NULL)
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

int	ft_lvl_up(char **line)
{
	char	*temp;
	int		lvl;

	temp = ft_strchr(*line, '=');
	temp++;
	lvl = ft_atoi(temp);
	if (lvl == 9)
		return (1);
	lvl++;
	free (*line);
	temp = ft_itoa(lvl);
	if (temp == NULL)
		return (2);
	*line = ft_strjoin("SHLVL=", temp);
	free (temp);
	if (*line == NULL)
		return (3);
	return (0);
}

int	ft_add_shlvl(t_envlst **env)
{
	char		*temp;
	t_envlst	*lst;

	temp = ft_strdup("SHLVL=1");
	if (temp == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (1);
	}
	lst = ft_lstnew_minishell(temp);
	if (lst == NULL)
	{
		ft_free_all(NULL, *env, NULL);
		return (2);
	}
	ft_lstadd_back_minishell(env, lst);
	return (0);
}
