/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:15:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/16 14:57:55 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_export_argument(char *todocmd, t_envlst *env, int destiny)
{
	t_envlst	*templst;

	if (ft_strchr(todocmd, '='))
	{	
		destiny = ft_search_and_replace(todocmd, env);
		if (destiny == 0 || destiny == -1)
			return (destiny);
		if (!todocmd[ft_search_char(todocmd, '=') + 1])
		{
			if (ft_export_arg_execute(todocmd, "", &templst))
				return (-1);
		}
		else
			if (ft_export_arg_execute(todocmd, todocmd
					+ ft_search_char(todocmd, '=') + 1, &templst))
				return (-1);
	}
	else
	{
		templst = ft_lstnew_minishell(ft_strdup(todocmd), ft_strdup(""), true);
		if (templst == NULL)
			return (-1);
	}
	ft_lstadd_back_minishell(&env, templst);
	return (0);
}

static void	ft_print_export(t_envlst *sorty, int fd)
{
	if (sorty->hidy)
		return ;
	else if (!sorty->indic)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(sorty->evar, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(sorty->cont, fd);
		ft_putendl_fd("\"", fd);
	}
	else
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(sorty->evar, fd);
	}
	sorty->sorty = true;
}

static t_envlst	*ft_get_smallest(t_envlst *env)
{
	t_envlst	*sorty;

	sorty = NULL;
	while (env)
	{
		if (!env->sorty)
		{
			sorty = env;
			break ;
		}
		env = env->next;
	}
	return (sorty);
}

static int	ft_export_no_argument(t_cmdline *todo, t_envlst *env)
{
	t_envlst	*temp;
	t_envlst	*sorty;
	int			i;

	i = -1;
	while (++i < ft_lstsize_minishell(env))
	{
		temp = env;
		sorty = ft_get_smallest(temp);
		while (temp)
		{
			if (ft_strncmp(sorty->evar, temp->evar, ft_strlen(sorty->evar)) > 0
				&& temp->sorty != 1)
				sorty = temp;
			temp = temp->next;
		}
		ft_print_export(sorty, todo->fd_out);
	}
	while (env)
	{
		env->sorty = false;
		env = env->next;
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
			if (ft_valid_export_cmd(todo->cmd[i]))
				return (1);
			else if (ft_export_argument(todo->cmd[i], env, 0))
				return (-1);
			i++;
		}
	}
	else
		ft_export_no_argument(todo, env);
	return (0);
}
