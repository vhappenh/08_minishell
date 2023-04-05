/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/05 14:45:00 by vhappenh         ###   ########.fr       */
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

char	*ft_doublejoin(char *str1, char *str2, char *str3)
{
	char	*temp;
	char	*fin;

	if (!str1 || !str2 || !str3)
		return (NULL);
	temp = ft_strjoin(str1, str2);
	if (temp == NULL)
		return (NULL);
	fin = ft_strjoin(temp, str3);
	if (fin == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (fin);
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
	t_envlst	*lst;

	i = -1;
	while (envp[++i])
	{
		lst = ft_lstnew_minishell(ft_strdup(envp[i]));
		if (lst == NULL)
			return (1);
		/*if (ft_strncmp(lst->line, "SHLVL=", 6))
		{
			if (ft_change_lvl(&lst->line))
				return (2);
		}*/
		ft_lstadd_back_minishell(env, lst);
	}
	return (0);
}

char	*get_env_path(t_envlst *env, char *pathname)
{
	char	*path;

	while (env)
	{
		if (!ft_strncmp(pathname, env->line, ft_strlen(pathname)))
			break ;
		env = env->next;
	}
	path = env->line;
	return (path);
}
