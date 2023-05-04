/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:48:21 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/04 11:49:20 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_search_and_replace(char *todocmd, t_envlst *env)
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

int	ft_export_arg_execute(char *str1, char *str2, t_envlst **temp)
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