/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/01 15:45:46 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_search_and_replace(char *todocmd, t_envlst *env)
{
	char	*temp;

	(void) env;
	temp = ft_strncopy(todocmd, ft_search_char(todocmd, '='));
	if (temp == NULL)
		return (1);
	while (env)
	{
		if (!ft_strncmp(temp, env->evar, ft_strlen(temp)))
		{
			free (env->cont);
			env->cont = ft_strdup(todocmd + ft_search_char(todocmd, '=') + 1);
			if (env->cont == NULL)
			{
				free (temp);
				return (2);
			}
			free (temp);
			env->indic = 0;
			return (0);
		}
		env = env->next;
	}
	free (temp);
	return (3);
}

static int	ft_export_arg_execute(char *str1, char *str2, t_envlst **temp)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strncopy(str1, ft_search_char(str1, '='));
	if (temp1 == NULL)
		return (1);
	temp2 = ft_strdup(str2);
	if (temp2 == NULL)
		return (1);
	*temp = ft_lstnew_minishell(ft_strdup(temp1), ft_strdup(temp2), 0);
	free (temp1);
	free (temp2);
	if (*temp == NULL)
		return (3);
	return (0);
}

static int	ft_export_argument(char *todocmd, t_envlst *env)
{
	t_envlst	*templst;

	if (!ft_search_and_replace(todocmd, env))
		return (0);
	if (ft_strchr(todocmd, '='))
	{	
		if (!todocmd[ft_search_char(todocmd, '=') + 1])
		{
			if (ft_export_arg_execute(todocmd, "", &templst))
				return (1);
		}
		else
			if (ft_export_arg_execute(todocmd, ft_strdup(todocmd
						+ ft_search_char(todocmd, '=') + 1), &templst))
				return (2);
	}
	else
	{
		templst = ft_lstnew_minishell(ft_strdup(todocmd), ft_strdup(""), 1);
		if (templst == NULL)
			return (3);
	}
	ft_lstadd_back_minishell(&env, templst);
	return (0);
}

static int	ft_export_no_argument(t_cmdline *todo, t_envlst *env)
{
	t_envlst	*temp;

	temp = env;
	while (temp)
	{
		if (!temp->indic)
		{
			ft_putstr_fd("declare -x ", todo->fd_out);
			ft_putstr_fd(temp->evar, todo->fd_out);
			ft_putstr_fd("=\"", todo->fd_out);
			ft_putstr_fd(temp->cont, todo->fd_out);
			ft_putendl_fd("\"", todo->fd_out);
		}
		else
		{
			ft_putstr_fd("declare -x ", todo->fd_out);
			ft_putendl_fd(temp->evar, todo->fd_out);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_export(t_cmdline *todo, t_envlst *env)
{
	int	i;

	i = 1;
	if (todo->cmd[i])
	{
		while (todo->cmd[i])
		{
			if (ft_export_argument(todo->cmd[i], env))
				return (1);
			i++;
		}
	}
	else
		if (ft_export_no_argument(todo, env))
			return (2);
	return (0);
}
