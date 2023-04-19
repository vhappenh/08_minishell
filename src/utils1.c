/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/19 10:40:35 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_djoin_spec(char *split_path, char **path, t_cmdline *todo)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(split_path, "/");
	if (temp1 == NULL)
		return (1);
	if (!todo->cmd[0])
	{
		free (temp1);
		return (2);
	}
	temp2 = ft_strjoin(temp1, todo->cmd[0]);
	free (temp1);
	if (temp2 == NULL)
		return (3);
	if (access(temp2, X_OK))
	{
		free (temp2);
		return (4);
	}
	*path = ft_strdup(temp2);
	free (temp2);
	return (0);
}

int	get_pwd(char **pwd)
{
	*pwd = ft_calloc(sizeof(char), 10000);
	if (*pwd == NULL)
		return (1);
	*pwd = getcwd(*pwd, 9999);
	if (*pwd == NULL)
	{
		perror("minishell");
		return (2);
	}
	return (0);
}

int	get_env(char **envp, t_envlst **env)
{
	int			i;
	int			shlvl;
	char		**input;
	t_envlst	*lst;

	i = -1;
	shlvl = 0;
	while (envp[++i])
	{
		input = ft_split(envp[i], '=');
		if (input == NULL)
			return (1);
		lst = ft_lstnew_minishell(ft_strdup(input[0]), ft_strdup(input[1]));
		if (lst == NULL)
			return (1);
		free (input[0]);
		free (input[1]);
		free (input);
		if (!ft_strncmp(lst->evar, "SHLVL", 6))
		{
			if (ft_lvl_up(&lst))
				if (!ft_free_lvl_fail(&lst, env))
					return (2);
			shlvl = 1;
		}
		ft_lstadd_back_minishell(env, lst);
	}
	if (shlvl == 0)
		if (ft_add_shlvl(env))
			return (3);
	return (0);
}

char	*get_env_path(t_envlst *env, char *pathname)
{
	char	*path;

	while (env)
	{
		if (!ft_strncmp(pathname, env->evar, ft_strlen(pathname) + 1))
			break ;
		env = env->next;
	}
	path = env->cont;
	return (path);
}
