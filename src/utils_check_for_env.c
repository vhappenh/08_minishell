/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_for_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:51:15 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/26 11:10:57 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static char	*ft_get_last_error(void)
{
	char	*tmp;

	tmp = ft_itoa(g_error);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*ft_search_return_env(char *env_name, t_envlst *env)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(env_name, "?", ft_strlen(env_name) + 1))
		return (ft_get_last_error());
	while (env)
	{
		if (!ft_strncmp(env_name, env->evar, ft_strlen(env_name) + 1))
		{
			tmp = ft_strdup(env->cont);
			if (tmp == NULL)
				return (NULL);
			break ;
		}
		else
			env = env->next;
	}
	if (tmp == NULL)
	{
		tmp = ft_strdup("");
		if (tmp == NULL)
			return (NULL);
	}
	return (tmp);
}

void	ft_skip_env(char **str, int *i)
{
	if ((*str)[(*i)] == '\'')
	{
		(*i)++;
		while ((*str)[(*i)] && (*str)[(*i)] != '\'')
			(*i)++;
	}
	else
	{
		(*i) += 2;
		while ((*str)[(*i)] == ' ')
			(*i)++;
		(*i) = ft_get_parse_len(*str, (*i));
	}
}
