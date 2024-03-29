/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:48:21 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/23 14:54:33 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_export_append(char *todocmd, t_envlst *env)
{
	char	*temp2;

	temp2 = ft_strjoin(env->cont, todocmd + ft_search_char(todocmd, '=') + 1);
	if (temp2 == NULL)
		return (-1);
	free (env->cont);
	env->cont = temp2;
	env->indic = 0;
	return (0);
}

static int	ft_export_replace(char *todocmd, t_envlst *env)
{
	free (env->cont);
	env->cont = ft_strdup(todocmd + ft_search_char(todocmd, '=') + 1);
	if (env->cont == NULL)
		return (-1);
	env->indic = 0;
	return (0);
}

int	ft_search_and_replace(char *todocmd, t_envlst *env)
{
	char	*temp;
	int		destiny;

	destiny = 1;
	if (todocmd[ft_search_char(todocmd, '=') - 1] == '+')
		temp = ft_strncopy(todocmd, ft_search_char(todocmd, '+'));
	else
		temp = ft_strncopy(todocmd, ft_search_char(todocmd, '='));
	if (temp == NULL)
		return (-1);
	while (env)
	{
		if (!ft_strncmp(temp, env->evar, ft_strlen(temp)))
		{
			if (todocmd[ft_search_char(todocmd, '=') - 1] == '+')
				destiny = ft_export_append(todocmd, env);
			else
				destiny = ft_export_replace(todocmd, env);
			break ;
		}
		env = env->next;
	}
	free (temp);
	return (destiny);
}

int	ft_export_arg_execute(char *str1, char *str2, t_envlst **temp)
{
	char	*temp1;
	char	*temp2;
	int		r;

	if (ft_search_char(str1, '+') < ft_search_char(str1, '=')
		&& ft_search_char(str1, '+') > 0)
		r = '+';
	else
		r = '=';
	temp1 = ft_strncopy(str1, ft_search_char(str1, r));
	temp2 = ft_strdup(str2);
	*temp = ft_lstnew_minishell(temp1, temp2, false);
	if (*temp == NULL)
		return (-1);
	return (0);
}

int	ft_valid_export_cmd(char *cmd)
{
	int	i;
	int	destiny;

	destiny = 0;
	i = -1;
	if (ft_isdigit(cmd[0]) || cmd[0] == '+' || cmd[0] == '=')
		destiny = 1;
	while (cmd[++i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_' && cmd[i] != '+')
			destiny = 1;
		if (cmd[i] == '+' && cmd[i + 1] != '=')
			destiny = 1;
	}
	if (destiny)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	return (destiny);
}
