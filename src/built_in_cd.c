/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:03:44 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/05 09:34:20 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_cd_select(char **pwd, char **new_path, t_cmdline *todo)
{
	int	i;

	i = 0;
	if (!todo->cmd[1])
	{
		*new_path = ft_strdup(getenv("HOME"));
		if (*new_path == NULL)
			i = 1;
	}
	else if (!ft_strncmp(todo->cmd[1], "..", 2) && !todo->cmd[1][2])
	{
		if (cd_dot_dot(*pwd, new_path))
			i = 2;
	}
	else
	{
		*new_path = ft_doublejoin(*pwd, "/", todo->cmd[1]);
		if (*new_path == NULL)
			i = 3;
	}
	if (i)
		free (*pwd);
	return (i);
}

int	ft_cd(t_cmdline *todo, t_envlst *env)
{
	char	*pwd;
	char	*new_path;

	(void)env;
	pwd = NULL;
	if (ft_get_pwd(&pwd))
		return (1);
	if (save_old_pwd(env, pwd))
	{
		free (pwd);
		return (2);
	}
	if (ft_cd_select(&pwd, &new_path, todo))
		return (3);
	free (pwd);
	if (save_pwd(env, new_path))
	{
		free (new_path);
		return (4);
	}
	if (chdir(new_path))
		printf("minishell: cd: %s: No such file or directory\n", todo->cmd[1]);
	free (new_path);
	return (0);
}
