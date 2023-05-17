/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_for_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:51:15 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/17 11:21:04 by rrupp            ###   ########.fr       */
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
