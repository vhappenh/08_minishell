/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:03:44 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/27 16:52:57 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	cd_dot_dot(char *pwd, char **new_path)
{
	int	i;
	int	new_len;

	i = -1;
	new_len = 0;
	while (pwd[++i])
		if (pwd[i] == '/')
			new_len = i;
	if (new_len == 0)
	{
		*new_path = ft_calloc(sizeof(char), 1 + 1);
		if (*new_path == NULL)
			return (-1);
		*new_path = ft_memcpy(*new_path, "/", 1);
	}
	else
	{
		*new_path = ft_calloc(sizeof(char), new_len + 1);
		if (*new_path == NULL)
			return (-1);
		*new_path = ft_memcpy(*new_path, pwd, new_len);
	}
	return (0);
}

static int	ft_save_pwd(t_envlst *env, char *pwd, char *evar)
{
	char		*temp;

	temp = ft_doublejoin(evar, "=", pwd);
	if (temp == NULL)
		return (1);
	if (ft_export_argument(temp, env, 0))
		return (-1);
	free (temp);
	free (pwd);
	return (0);
}

static int	ft_cd_select(char **pwd, char **new_path, t_cmdline *todo)
{
	if (!todo->cmd[1])
		*new_path = ft_search_return_env("~", todo->enviroment);
	else if (!ft_strncmp(todo->cmd[1], "..", 3) && !todo->cmd[2])
		return (cd_dot_dot(*pwd, new_path));
	else if (todo->cmd[1][0] == '/' && !todo->cmd[2])
		*new_path = ft_strdup(todo->cmd[1]);
	else if (!ft_strncmp(todo->cmd[1], "-", 2) && !todo->cmd[2])
		*new_path = ft_search_return_env("OLDPWD", todo->enviroment);
	else if (!todo->cmd[2])
		*new_path = ft_doublejoin(*pwd, "/", todo->cmd[1]);
	else
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (*new_path == NULL)
		return (-1);
	return (0);
}

int	ft_cd(t_cmdline *todo, t_envlst *env)
{
	char	*pwd;
	char	*new_path;

	pwd = NULL;
	if (ft_get_pwd(&pwd))
		return (-1);
	g_error = ft_cd_select(&pwd, &new_path, todo);
	if (g_error == -1 || g_error == 1)
		return (g_error);
	if (ft_save_pwd(env, pwd, "OLDPWD"))
		return (-1);
	if (chdir(new_path))
	{
		ft_putstr_fd("minishell: cd:", 2);
		ft_putstr_fd(new_path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free (new_path);
		return (1);
	}
	if (ft_save_pwd(env, new_path, "PWD"))
		return (-1);
	return (0);
}
