/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/19 10:48:19 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_export_argument(t_cmdline *todo, t_envlst *env)
{
	int			i;
	char		**temp;
	t_envlst	*templst;

	i = 0;
	while (todo->cmd[++i])
	{
		if (ft_strchr(todo->cmd[i], '='))
		{	
			temp = ft_split(todo->cmd[i], '=');
			if (temp == NULL)
				return (1);
			templst = ft_lstnew_minishell(ft_strdup(temp[0]), ft_strdup(temp[1]));
			if (templst == NULL)
				return (2);
			ft_lstadd_back_minishell(&env, templst);
		}
	}
	return (0);
}

static int	ft_export_no_argument(t_cmdline *todo, t_envlst *env)
{
	(void) todo;
	(void) env;
	write(1, "exportlst\n", 11);
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
