/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:03:44 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/10 11:24:53 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	cd_dot_dot(char *pwd, char **new_path)
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

static int	ft_save_pwd(t_envlst *env, char *pwd, char *evar)
{
	while (env)
	{
		if (!ft_strncmp(env->evar, evar, ft_strlen(evar) + 1))
		{
			free (env->cont);
			env->cont = ft_strdup(pwd);
			if (env->cont == NULL)
			{
				free (pwd);
				return (1);
			}
			break ;
		}
		env = env->next;
	}
	free (pwd);
	return (0);
}

static int	ft_cd_select(char **pwd, char **new_path, t_cmdline *todo)
{
	int	i;

	i = 0;
	if (!todo->cmd[1])
	{
		*new_path = ft_strdup(getenv("HOME"));
		if (*new_path == NULL)
			i = -1;
	}
	else if (!ft_strncmp(todo->cmd[1], "..", 3) && !todo->cmd[2])
		i = cd_dot_dot(*pwd, new_path);
	else if (todo->cmd[1][0] == '/' && !todo->cmd[2])
	{
		*new_path = ft_strdup(todo->cmd[1]);
		if (*new_path == NULL)
			i = -1;
	}
	else if (!todo->cmd[2])
	{
		*new_path = ft_doublejoin(*pwd, "/", todo->cmd[1]);
		if (*new_path == NULL)
			i = -1;
	}
	else
	{
		ft_putendl_fd("minishell: cd: too many arguments", todo->fd_out);
		i = -1;
	}
	return (i);
}

int	ft_cd(t_cmdline *todo, t_envlst *env)
{
	char	*pwd;
	char	*new_path;

	pwd = NULL;
	if (ft_get_pwd(&pwd))
		return (1);
	if (ft_cd_select(&pwd, &new_path, todo))
		return (2);
	if (ft_save_pwd(env, pwd, "OLDPWD"))
		return (3);
	if (chdir(new_path))
	{
		printf("minishell: cd: %s: No such file or directory\n", new_path);
		free (new_path);
		return (4);
	}
	if (ft_save_pwd(env, new_path, "PWD"))
		return (5);
	return (0);
}
