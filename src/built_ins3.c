/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/20 13:14:31 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_export_argument(t_cmdline *todo, t_envlst *env)
{
	char		*temp1;
	char		*temp2;
	t_envlst	*templst;

	if (ft_strchr(todo->cmd[1], '='))
	{	
		if (!todo->cmd[1][ft_search_char(todo->cmd[1], '=') + 1])
		{
			temp1 = ft_strncopy(todo->cmd[1],
					ft_search_char(todo->cmd[1], '='));
			if (temp1 == NULL)
				return (1);
			temp2 = ft_strdup("");
			if (temp2 == NULL)
				return (1);
			templst = ft_lstnew_minishell(ft_strdup(temp1), ft_strdup(temp2));
			free (temp1);
			free (temp2);
			if (templst == NULL)
				return (3);
		}
		else
		{		
			temp1 = ft_strncopy(todo->cmd[1],
					ft_search_char(todo->cmd[1], '='));
			if (temp1 == NULL)
				return (1);
			temp2 = ft_strdup(todo->cmd[1]
					+ ft_search_char(todo->cmd[1], '=') + 1);
			if (temp2 == NULL)
				return (1);
			templst = ft_lstnew_minishell(ft_strdup(temp1), ft_strdup(temp2));
			free (temp1);
			free (temp2);
			if (templst == NULL)
				return (3);
		}
		ft_lstadd_back_minishell(&env, templst);
	}
	return (0);
}

static int	ft_export_no_argument(t_cmdline *todo, t_envlst *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", todo->fd_out);
		ft_putstr_fd(env->evar, todo->fd_out);
		ft_putstr_fd("=\"", todo->fd_out);
		ft_putstr_fd(env->cont, todo->fd_out);
		ft_putendl_fd("\"", todo->fd_out);
		env = env->next;
	}
	return (0);
}

int	ft_export(t_cmdline *todo, t_envlst *env)
{
	if (todo->cmd[1])
	{
		if (ft_export_argument(todo, env))
			return (1);
	}
	else
	{
		if (ft_export_no_argument(todo, env))
			return (2);
	}
	return (0);
}
