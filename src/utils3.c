/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/05 13:15:52 by vhappenh         ###   ########.fr       */
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
