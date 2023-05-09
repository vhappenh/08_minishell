/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_for_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:51:15 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/09 15:40:46 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static char	*ft_get_last_error(int err)
{
	char	*tmp;

	if (err == 4)
		tmp = ft_strdup("130");
	else
		tmp = ft_itoa(err);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*ft_search_return_env(char *env_name, t_envlst *env, int err)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(env_name, "?", ft_strlen(env_name) + 1))
		return (ft_get_last_error(err));
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
