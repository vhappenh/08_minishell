/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_for_env_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:51:15 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/28 15:11:15 by vhappenh         ###   ########.fr       */
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

static char	*ft_get_tilde(char *env_name, t_envlst *env)
{
	char	*ret;

	if (!ft_strncmp(env_name, "~+", 3))
	{
		ret = ft_search_return_env("PWD", env);
		if (ret && *ret == '\0')
		{
			free(ret);
			ret = ft_strdup("~+");
		}
	}
	else
	{
		ret = ft_search_return_env("OLDPWD", env);
		if (ret && *ret == '\0')
		{
			free(ret);
			ret = ft_strdup("~-");
		}		
	}
	if (ret == NULL)
		return (NULL);
	return (ret);
}

static char	*ft_search_for_real(char *env_name, t_envlst *env)
{
	char	*tmp;

	tmp = NULL;
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

char	*ft_search_return_env(char *env_name, t_envlst *env)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(env_name, "?", ft_strlen(env_name) + 1))
		return (ft_get_last_error());
	else if (!ft_strncmp(env_name, "~+", 3) || !ft_strncmp(env_name, "~-", 3))
		return (ft_get_tilde(env_name, env));
	else
		tmp = ft_search_for_real(env_name, env);
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
